/// shader_high_fog_set()

var uTexture = shader_get_sampler_index(shader_high_fog, "uTexture"), 
	uAlpha = shader_get_uniform(shader_high_fog, "uAlpha");

shader_set(shader_high_fog)

shader_set_texture(uTexture, shader_texture)
	
shader_set_uniform_f(uAlpha, shader_alpha)

shader_set_fog(shader_high_fog)
shader_set_wind(shader_high_fog)
