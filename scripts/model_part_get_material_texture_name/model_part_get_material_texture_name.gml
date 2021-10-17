/// model_part_get_material_texture_name(part, map)
/// @arg part
/// @arg map

function model_part_get_material_texture_name(part, map)
{
	var key;
	
	if (part = null)
		return map[?""]
	
	if (part.object_index = obj_model_part)
		key = part.name
	else // Root
		key = ""
	
	// State-specific texture
	if (!is_undefined(map[?key]))
		return map[?key]
	
	// Part-specific texture
	if (part.texture_material_name != "")
		return part.texture_material_name
	
	// Get texture of inherited part
	return model_part_get_material_texture_name(part.texture_inherit, map)
}
