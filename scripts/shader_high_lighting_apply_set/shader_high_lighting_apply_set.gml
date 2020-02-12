/// shader_high_lighting_apply_set(ssao, shadows, mask)
/// @arg ssao
/// @arg shadows
/// @arg mask

render_set_uniform_int("uSSAOEnabled", app.setting_render_ssao)

if (app.setting_render_ssao && surface_exists(argument0))
	texture_set_stage(sampler_map[?"uSSAO"], surface_get_texture(argument0))

render_set_uniform_int("uShadowsEnabled", app.setting_render_shadows)

if (app.setting_render_shadows && surface_exists(argument1))
	texture_set_stage(sampler_map[?"uShadows"], surface_get_texture(argument1))

texture_set_stage(sampler_map[?"uMask"], surface_get_texture(argument2))

render_set_uniform_color("uAmbientColor", app.background_ambient_color_final, 1)
