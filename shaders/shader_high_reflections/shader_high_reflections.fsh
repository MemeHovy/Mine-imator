varying vec2 vTexCoord;

// Buffers
uniform sampler2D uDiffuseBuffer;
uniform sampler2D uDepthBuffer;
uniform sampler2D uNormalBuffer;
uniform sampler2D uNormalBufferExp;
uniform sampler2D uMaterialBuffer;

// Camera data
uniform mat4 uProjMatrix;
uniform mat4 uProjMatrixInv;
uniform mat4 uViewMatrix;
uniform mat4 uViewMatrixInv;
uniform float uNear;
uniform float uFar;
uniform vec2 uScreenSize;

uniform float uPrecision;
uniform float uThickness;
uniform float uOffset[16];
uniform vec4 uFallbackColor;

// Unpacks depth value from packed color
float unpackDepth(vec4 c)
{
	return c.r + c.g / 255.0 + c.b / (255.0 * 255.0);
}

// Returns depth value from packed depth buffer
float getDepth(vec2 coords)
{
	return unpackDepth(texture2D(uDepthBuffer, coords));
}

// Transforms Z depth with camera data
float transformDepth(float depth)
{
	return (uFar - (uNear * uFar) / (depth * (uFar - uNear) + uNear)) / (uFar - uNear);
}

// Reconstruct a position from a screen space coordinate and (linear) depth
vec4 posFromBuffer(vec2 coord, float depth)
{
	vec4 pos = uProjMatrixInv * vec4(coord.x * 2.0 - 1.0, 1.0 - coord.y * 2.0, transformDepth(depth), 1.0);
	return vec4(pos.xyz / pos.w, pos.w);
}

float unpackFloat2(float expo, float dec)
{
	return (expo * 255.0 * 255.0) + (dec * 255.0);
}

// Get normal Value
vec3 getNormal(vec2 coords)
{
	vec3 nDec = texture2D(uNormalBuffer, coords).rgb;
	vec3 nExp = texture2D(uNormalBufferExp, coords).rgb;
	
	return (vec3(unpackFloat2(nExp.r, nDec.r), unpackFloat2(nExp.g, nDec.g), unpackFloat2(nExp.b, nDec.b)) / (255.0 * 255.0)) * 2.0 - 1.0;
}

// Hash scatter function
#define SCALE vec3(.8, .8, .8)
#define K 19.19

vec3 hash(vec3 a)
{
	a = fract(a * SCALE);
	a += dot(a, a.yxz + K);
	return fract((a.xxy + a.yxx) * a.zyx);
}

vec2 viewPosToPixel(vec4 viewPos)
{
	viewPos     *= uProjMatrix;
	viewPos.xyz /= viewPos.w;
	viewPos.xy   = viewPos.xy * 0.5 + 0.5;
	viewPos.xy  *= uScreenSize;
	
	return viewPos.xy;
}

// Fresnel Schlick approximation
float fresnelSchlick(float cosTheta, float F0)
{
	return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

// Ray tracer, returns color
vec3 rayTrace(vec2 originUV)
{
	vec3 traceCol = vec3(0.0);
	
	// Material from UV
	vec3 mat = texture2D(uMaterialBuffer, originUV).rgb;
	float metallic  = mat.r;
	float roughness = mat.g;
	float fresnel   = mat.b;
	
	// Sample buffers
	float originDepth = getDepth(originUV);
	vec4 viewPos = posFromBuffer(originUV, originDepth);
	vec3 worldPos = vec3(vec4(viewPos.xyz, 1.0) * uViewMatrixInv);
	vec3 normal = getNormal(originUV);
	
	vec3 jitt;
	vec3 rayVector;
		
	// Randomize vector until valid
	for (int i = 0; i < 16; i++)
	{
		jitt = mix(vec3(0.0), (vec3(hash(worldPos + float(uOffset[i]))) - 0.5) * 2.0, mix(0.0, 1.0, pow(roughness, 2.5)));
		rayVector = normalize(reflect(normalize(viewPos.xyz), normal + jitt));
			
		if (dot(rayVector, normal) > 0.0)
			break;
	}
	
	// Pixel coord on texture
	vec2 pixelCoord = uScreenSize / originUV;
	
	// Ray data
	float raySize       = 5000.0;
	vec4 rayStartPos    = vec4(viewPos.xyz + (rayVector * 3.0),     1.0);
	vec4 rayEndPos      = vec4(viewPos.xyz + (rayVector * raySize), 1.0);
	vec2 rayStartPixel  = viewPosToPixel(rayStartPos);
	vec2 rayEndPixel    = viewPosToPixel(rayEndPos);
	vec2 rayPixel       = rayStartPixel;
	vec2 rayUV          = rayPixel / uScreenSize;
	
	// Trace data
	vec2 pixelDelta     = rayEndPixel - rayStartPixel;
	bool useDeltaX      = (abs(pixelDelta.x) >= abs(pixelDelta.y));
	float stepDelta     = (useDeltaX ? abs(pixelDelta.x) : abs(pixelDelta.y)) * clamp(uPrecision, 0.0, 1.0);
	vec2 pixelStepDelta = pixelDelta / max(stepDelta, 0.001);
	vec4 samplePos      = viewPos;
	
	int refineSteps = 5;
	float progress = 0.0;
	float progressPrev = 0.0;
	float vis = 0.0;
	
	float viewDist = originDepth;
	float depth    = uThickness;
	
	for (int i = 0; i < int(stepDelta); i++)
	{
		rayPixel += pixelStepDelta;
		rayUV     = rayPixel / uScreenSize;
		rayUV.x   = 1.0 - rayUV.x;
		
		samplePos = posFromBuffer(rayUV, getDepth(rayUV));
		
		progress  = (useDeltaX ?
					((rayPixel.x - rayStartPixel.x) / pixelDelta.x) :
					((rayPixel.y - rayStartPixel.y) / pixelDelta.y));
		
		progress  = clamp(progress, 0.0, 1.0);
		
		viewDist  = (rayStartPos.z * rayEndPos.z) / mix(rayEndPos.z, rayStartPos.z, progress);
		depth     = viewDist - samplePos.z;
		
		// Check for collision, if no collision, 
		if (depth > 0.0 && depth < uThickness)
		{
			vis = 1.0;
			break;
		}
		else
			progressPrev = progress;
		
		if (samplePos.z <= 0.0 || rayUV.x <= 0.0 || rayUV.x >= 1.0 || rayUV.y <= 0.0 || rayUV.y >= 1.0)
		{
			vis = 0.0;
			break;
		}
	}
	
	// Refine ray UV
	if (vis < 1.0)
		refineSteps = 0;
	
	progress = progressPrev + ((progress - progressPrev) / 2.0);
	
	for (int i = 0; i < refineSteps; i++)
	{
		rayPixel  = mix(rayStartPixel, rayEndPixel, progress);
		rayUV     = rayPixel / uScreenSize;
		rayUV.x   = 1.0 - rayUV.x;
		
		samplePos = posFromBuffer(rayUV, getDepth(rayUV));
		
		viewDist  = (rayStartPos.z * rayEndPos.z) / mix(rayEndPos.z, rayStartPos.z, progress);
		depth     = viewDist - samplePos.z;
		
		if (depth > 0.0 && depth < uThickness)
		{
			vis = 1.0;
			progress = progressPrev + ((progress - progressPrev) / 2.0);
		}
		else
		{
			float temp   = progress;
			progress     = progressPrev + ((progress - progressPrev) / 2.0);
			progressPrev = temp;
		}
	}
		
	traceCol = uFallbackColor.rgb;
	
	// Visible, must've hit something.
	if (vis > 0.0)
	{
		vis *= (1.0 - clamp(depth / uThickness, 0.0, 1.0));
		vis *= (1.0 - clamp(length(samplePos - viewPos) / raySize, 0.0, 1.0));
		vis *= rayVector.z;
		
		// Fade by edge
		vec2 fadeUV = smoothstep(0.2, 0.6, abs(vec2(0.5, 0.5) - rayUV.xy));
		vis *= clamp(1.0 - (fadeUV.x + fadeUV.y), 0.0, 1.0);
		
		// Clamp
		vis = clamp(vis, 0.0, 1.0);
		
		// Mix in fallback via fresnel if ray hit a reflective surface ¯\_(ツ)_/¯
		vec3 surfCol = mix(texture2D(uDiffuseBuffer, rayUV).rgb, uFallbackColor.rgb, texture2D(uMaterialBuffer, rayUV).b);
		traceCol = mix(traceCol, surfCol, vis);
	}
	
	// Fade based on Fresnel/roughness
	traceCol *= fresnel;
	
	return traceCol;
}

void main()
{
	// Perform alpha test to ignore background
	if (texture2D(uDepthBuffer, vTexCoord).a < 1.0)
		discard;
	
	vec3 result = rayTrace(vTexCoord);
	
	gl_FragColor = vec4(result, 1.0);
}