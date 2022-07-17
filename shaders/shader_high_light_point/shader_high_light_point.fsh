#define SQRT05 0.707106781
#define PI 3.14159265

uniform sampler2D uTexture;
uniform vec2 uTexScale;
uniform vec4 uBlendColor;
uniform int uIsSky;
uniform int uIsWater;

uniform vec3 uLightPosition;
uniform vec4 uLightColor;
uniform float uLightStrength;
uniform float uLightNear;
uniform float uLightFar;
uniform float uLightFadeSize;
uniform vec3 uShadowPosition;
uniform float uSpecularStrength;
uniform float uLightSize;

uniform sampler2D uDepthBuffer;
uniform float uDepthBufferSize;

uniform sampler2D uTextureMaterial;
uniform vec2 uTexScaleMaterial;
uniform int uMaterialUseGlossiness;

uniform sampler2D uTextureNormal;
uniform vec2 uTexScaleNormal;

uniform float uSSS;
uniform vec3 uSSSRadius;
uniform vec4 uSSSColor;

uniform vec3 uCameraPosition;
uniform float uRoughness;
uniform float uMetallic;

varying vec3 vPosition;
varying vec3 vNormal;
varying vec2 vTexCoord;
varying float vBlockSSS;

// Fresnel Schlick approximation
float fresnelSchlick(float cosTheta, float F0, float F90)
{
	return F0 + (F90 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

// GGX specular (https://learnopengl.com/PBR/Lighting)
float distributionGGX(vec3 N, vec3 H, float roughness)
{
    float a2      = roughness * roughness * roughness * roughness;
    float NdotH  = max(dot(N, H), 0.0);
    float denom = (NdotH * NdotH * (a2 - 1.0) + 1.0);
    return a2 / (PI * denom * denom);
}

float geometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;
	
	return NdotV / (NdotV * (1.0 - k) + k);
}

float geometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    return	geometrySchlickGGX(max(dot(N, V), 0.0), roughness) *
			geometrySchlickGGX(max(dot(N, L), 0.0), roughness);
}

#extension GL_OES_standard_derivatives : enable
vec3 getMappedNormal(vec3 N, vec3 pos, vec2 uv)
{
	// Get edge derivatives
	vec3 posDx = dFdx(pos);
	vec3 posDy = dFdy(pos);
	vec2 uvDx = dFdx(uv);
	vec2 uvDy = dFdy(uv);
	
	// Calculate tangent/bitangent
	vec3 posPx = cross(N, posDx);
	vec3 posPy = cross(posDy, N);
	vec3 T = normalize(posPy * uvDx.x + posPx * uvDy.x);
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);
	
	// Create a Scale-invariant frame
	float invmax = pow(max(dot(T, T), dot(B, B)), -0.5);  
	
	// Build TBN matrix to transform mapped normal with mesh
	mat3 TBN = mat3(T * invmax, B * invmax, N);
	
	vec3 texColor = normalize(texture2D(uTextureNormal, uv).rgb * 2.0 - 1.0);
	return normalize(TBN * texColor);
}

float unpackDepth(vec4 c)
{
	return c.r + c.g / 255.0 + c.b / (255.0 * 255.0);
}

vec2 getShadowMapCoord(vec3 look)
{
	float tFOV = tan(PI / 4.0);
	vec3 u, v, toPoint = vPosition - uShadowPosition;
	vec2 coord;
	
	// Prepare 3D to 2D conversion
	look /= sqrt(dot(look, look));
	u = vec3(-look.z * look.x, -look.z * look.y, 1.0 - look.z * look.z);
	u /= sqrt(dot(u, u));
	u *= tFOV; 
	v = vec3(u.y * look.z - look.y * u.z, u.z * look.x - look.z * u.x, u.x * look.y - look.x * u.y);
	
	// Convert
	toPoint /= dot(toPoint,look);
	coord.x = (dot(toPoint, v) / (tFOV * tFOV) + 1.0) * 0.5;
	coord.y = (1.0 - dot(toPoint, u) / (tFOV * tFOV)) * 0.5;
	
	coord.x /= 3.0;
	coord.y *= 0.5;
	
	return coord;
}

// Linear filtering, done in-shader as we use a texture atlas
vec4 getFilteredDepth(vec2 uv, vec2 uvMin)
{
	float samples;
	vec2 sampleuv, uvMax, texelOffset;
	vec4 color = vec4(0.0);
	texelOffset = vec2((1.0/vec2(uDepthBufferSize * 3.0, uDepthBufferSize * 2.0)) * 0.5);
	uvMax = uvMin + vec2(1.0/3.0, 0.5);
	
	// Top left
	sampleuv = uv - texelOffset.x;
	if (sampleuv.x > uvMin.x && sampleuv.x < uvMax.x &&
		sampleuv.y > uvMin.y && sampleuv.y < uvMax.y)
	{
		color += texture2D(uDepthBuffer, sampleuv);
		samples += 1.0;
	}
	
	// Top right
	sampleuv.y = uv.y - texelOffset.x;
	sampleuv.x = uv.x + texelOffset.y;
	if (sampleuv.x > uvMin.x && sampleuv.x < uvMax.x &&
		sampleuv.y > uvMin.y && sampleuv.y < uvMax.y)
	{
		color += texture2D(uDepthBuffer, sampleuv);
		samples += 1.0;
	}
	
	// Bottom left
	sampleuv.y = uv.y + texelOffset.x;
	sampleuv.x = uv.x - texelOffset.y;
	if (sampleuv.x > uvMin.x && sampleuv.x < uvMax.x &&
		sampleuv.y > uvMin.y && sampleuv.y < uvMax.y)
	{
		color += texture2D(uDepthBuffer, sampleuv);
		samples += 1.0;
	}
	
	// Bottom right
	sampleuv = uv + texelOffset;
	if (sampleuv.x > uvMin.x && sampleuv.x < uvMax.x &&
		sampleuv.y > uvMin.y && sampleuv.y < uvMax.y)
	{
		color += texture2D(uDepthBuffer, sampleuv);
		samples += 1.0;
	}
	
	return color / samples;
}

void main()
{
	vec3 light, spec;
	int sssEnabled = (vBlockSSS + uSSS > 0.0 ? 1 : 0);
	
	vec2 tex = vTexCoord;
	if (uTexScale.x < 1.0 || uTexScale.y < 1.0)
		tex = mod(tex * uTexScale, uTexScale); // GM sprite bug workaround
	vec4 baseColor = texture2D(uTexture, tex);
	
	if (uIsSky > 0)
	{
		light = vec3(0.0);
		spec = vec3(uSpecularStrength);
	}
	else
	{
		// Get material data
		vec2 texMat = vTexCoord;
		if (uTexScaleMaterial.x < 1.0 || uTexScaleMaterial.y < 1.0)
			texMat = mod(texMat * uTexScaleMaterial, uTexScaleMaterial); // GM sprite bug workaround
		
		vec2 normalTex = vTexCoord;
		if (uTexScaleNormal.x < 1.0 || uTexScaleNormal.y < 1.0)
			normalTex = mod(normalTex * uTexScaleNormal, uTexScaleNormal); // GM sprite bug workaround
		
		vec3 mat = texture2D(uTextureMaterial, texMat).rgb;
		float roughness = max(0.02, 1.0 - ((1.0 - uRoughness) * (uMaterialUseGlossiness == 0 ? 1.0 - mat.r : mat.r)));
		float metallic = (mat.g * uMetallic);
		
		float shadow = 1.0;
		float att = 0.0;
		vec3 subsurf = vec3(0.0);
		
		// Diffuse factor
		vec3 normal = getMappedNormal(vNormal, vPosition, normalTex);
		float dif = max(0.0, dot(normalize(normal), normalize(uLightPosition - vPosition))); 
		
		// Attenuation factor
		att = 1.0 - clamp((distance(vPosition, uLightPosition) - uLightFar * (1.0 - uLightFadeSize)) / (uLightFar * uLightFadeSize), 0.0, 1.0); 
		dif *= att;
		
		if (dif > 0.0 || sssEnabled == 1)
		{
			int buffer;
			vec2 fragCoord, bufferMin, bufferMax;
			vec3 toLight = vPosition - uShadowPosition;
			vec4 lookDir = vec4( // Get the direction from the pixel to the light
				toLight.x / distance(vPosition.xy, uShadowPosition.xy),
				toLight.y / distance(vPosition.xy, uShadowPosition.xy),
				toLight.z / distance(vPosition.xz, uShadowPosition.xz),
				toLight.z / distance(vPosition.yz, uShadowPosition.yz)
			);
		
			// Get shadow map and texture coordinate
		
			// Z+
			// ooo
			// oxo
			if (lookDir.z > SQRT05 && lookDir.w > SQRT05)
			{ 
				buffer = 4;
				fragCoord = getShadowMapCoord(vec3(0.0, -0.0001, 1.0));
				fragCoord.x += 1.0/3.0;
				fragCoord.y += 0.5;
				
				bufferMin = vec2(1.0/3.0, 0.5);
			}
			
			// Z-
			// ooo
			// oox
			else if (lookDir.z < -SQRT05 && lookDir.w < -SQRT05)
			{
				buffer = 5;
				fragCoord = getShadowMapCoord(vec3(0.0, -0.0001, -1.0));
				fragCoord.x += 2.0/3.0;
				fragCoord.y += 0.5;
				
				bufferMin = vec2(2.0/3.0, 0.5);
			}
		
			// X+
			// xoo
			// ooo
			else if (lookDir.x > SQRT05)
			{ 
				buffer = 0;
				fragCoord = getShadowMapCoord(vec3(1.0, 0.0, 0.0));
				
				bufferMin = vec2(0.0);
			}
		
			// X-
			// oxo
			// ooo
			else if (lookDir.x < -SQRT05)
			{
				buffer = 1;
				fragCoord = getShadowMapCoord(vec3(-1.0, 0.0, 0.0));
				fragCoord.x += 1.0/3.0;
				
				bufferMin = vec2(1.0/3.0, 0.0);
			}
		
			// Y+
			// oox
			// ooo
			else if (lookDir.y > SQRT05)
			{ 
				buffer = 2;
				fragCoord = getShadowMapCoord(vec3(0.0, 1.0, 0.0));
				fragCoord.x += 2.0/3.0;
				
				bufferMin = vec2(2.0/3.0, 0.0);
			}
		
			// Y-
			// ooo
			// xoo
			else
			{ 
				buffer = 3;
				fragCoord = getShadowMapCoord(vec3(0.0, -1.0, 0.0));
				fragCoord.y += 0.5;
				
				bufferMin = vec2(0.0, 0.5);
			}
			
			// Calculate bias
			float bias = 1.0;
			
			// Shadow
			float fragDepth = distance(vPosition, uShadowPosition);
			float sampleDepth = uLightNear + (uLightFar - uLightNear) * unpackDepth(getFilteredDepth(fragCoord, bufferMin));//texture2D(uDepthBuffer, fragCoord));
			shadow = ((fragDepth - bias) > sampleDepth) ? 0.0 : 1.0;
			
			if (sssEnabled == 1)
			{
				// Get subsurface translucency
				vec3 dis = vec3(uSSSRadius * max(uSSS, vBlockSSS));
				float lightdis = (fragDepth + bias) - sampleDepth;
				
				if (dif == 0.0 && ((fragDepth + bias) > sampleDepth || vBlockSSS > 0.0))
				{
					if (vBlockSSS > 0.0 && (fragDepth - (bias * 0.01)) <= sampleDepth)
						lightdis = 0.0;
					
					subsurf = vec3(vec3(1.0) - clamp(vec3(lightdis) / dis, vec3(0.0), vec3(1.0)));
					subsurf *= att;
				}
			}
		}
		
		// Diffuse light
		light = uLightColor.rgb * uLightStrength * dif * shadow;
		
		// Subsurface translucency
		float transDif = max(0.0, dot(normalize(-normal), normalize(uLightPosition - vPosition)));
		transDif = clamp(transDif, 0.0, 1.0);
		subsurf *= (uLightColor.rgb * uLightStrength * uSSSColor.rgb * transDif);
		light += subsurf;
		light *= mix(vec3(1.0), uSSSColor.rgb, clamp(uSSS/16.0, 0.0, 1.0));
		
		// Calculate specular
		vec3 N   = normal;
		vec3 V   = normalize(uCameraPosition - vPosition);
		vec3 L   = normalize(uLightPosition - vPosition);
		vec3 H   = normalize(V + L);
		float NDF = distributionGGX(N, H, roughness);       
		float G   = geometrySmith(N, V, L, roughness);
		
		float F0, F90, F;
		F0 = mix(mix(0.04, 0.0, roughness), 1.0, metallic);
		F90 = mix(mix(0.7, 0.0, roughness), 1.0, metallic);
		F = fresnelSchlick(max(dot(H, V), 0.0), F0, F90);
		
		float numerator    = NDF * G * F;
		float denominator  = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
		float specular     = numerator / denominator;
		
		spec = uLightColor.rgb * shadow * uSpecularStrength * dif * (specular * mix(vec3(1.0), baseColor.rgb * uBlendColor.rgb, metallic));
	}
	
	gl_FragData[0] = vec4(light, uBlendColor.a * baseColor.a);
	gl_FragData[1] = vec4(spec, uBlendColor.a * baseColor.a);
	
	if (uBlendColor.a * baseColor.a == 0.0)
		discard;
}
