/// project_load_values_update_name(name)
/// @arg name

function project_load_values_update_name(name)
{
	if (load_format < e_project.FORMAT_130_AL10)
	{
		if (name = "BG_SKY_CLOUDS_Z")
			return "BG_SKY_CLOUDS_HEIGHT"
	}
	
	return name;
}
