/// temp_event_destroy()
/// @desc Destroy event of templates

function temp_event_destroy()
{
	if (model_texture_name_map != null)	
		ds_map_destroy(model_texture_name_map)
	
	if (model_texture_material_name_map != null)	
		ds_map_destroy(model_texture_material_name_map)
	
	if (model_tex_normal_name_map != null)	
		ds_map_destroy(model_tex_normal_name_map)
	
	if (model_shape_texture_name_map != null)	
		ds_map_destroy(model_shape_texture_name_map)
	
	if (model_shape_texture_material_name_map != null)	
		ds_map_destroy(model_shape_texture_material_name_map)
	
	if (model_shape_tex_normal_name_map != null)	
		ds_map_destroy(model_shape_tex_normal_name_map)
	
	if (model_hide_list != null)
		ds_list_destroy(model_hide_list)
	
	if (model_shape_hide_list != null)
		ds_list_destroy(model_shape_hide_list)
	
	if (model_shape_vbuffer_map != null && ds_map_size(model_shape_vbuffer_map) > 0)
	{
		model_shape_clear_cache(model_shape_cache_list, true)
		ds_map_destroy(model_shape_vbuffer_map)
	}
	
	if (model_shape_alpha_map != null)
		ds_map_destroy(model_shape_alpha_map)
	
	if (temp_creator != app.bench_settings)
	{
		if (model_tex != null)
			model_tex.count--
		
		if (model_tex_material != null)
			model_tex_material.count--
		
		if (model_tex_normal != null)
			model_tex_normal.count--
		
		if (item_tex != null)
			item_tex.count--
		
		if (item_tex_material != null)
			item_tex_material.count--
		
		if (item_tex_normal != null)
			item_tex_normal.count--
		
		if (block_tex != null)
			block_tex.count--
		
		if (block_tex_material != null)
			block_tex_material.count--
		
		if (block_tex_normal != null)
			block_tex_normal.count--
		
		if (scenery > 0)
			scenery.count--
		
		if (shape_tex != null && shape_tex.type != e_tl_type.CAMERA)
			shape_tex.count--
		
		if (shape_tex_material != null)
			shape_tex_material.count--
		
		if (shape_tex_normal != null)
			shape_tex_normal.count--
		
		if (text_font != null)
			text_font.count--
	}
	
	if (item_vbuffer != null)
		vbuffer_destroy(item_vbuffer)
	
	if (type = e_temp_type.BLOCK || type = e_temp_type.SCENERY)
		block_vbuffer_destroy()
	
	if (type = e_temp_type.PARTICLE_SPAWNER)
		temp_particles_type_clear()
	
	with (obj_timeline)
		if (temp = other.id && part_of == null && !delete_ready)
			tl_remove_clean()
	
	with (obj_timeline)
		if (delete_ready)
			instance_destroy()
	
	with (obj_particle_type)
		if (temp = other.id)
			temp = null
	
	temp_edit = sortlist_remove(app.lib_list, id)
}
