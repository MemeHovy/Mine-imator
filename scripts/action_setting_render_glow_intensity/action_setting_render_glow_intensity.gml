/// action_setting_render_glow_intensity(value, add)
/// @arg value
/// @arg add

function action_setting_render_glow_intensity(val, add)
{
	setting_render_glow_intensity = setting_render_glow_intensity * add + val / 100
}
