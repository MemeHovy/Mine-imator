/// action_lib_pc_type_sprite_animation_speed_random_max(value, add)
/// @arg value
/// @arg add

function action_lib_pc_type_sprite_animation_speed_random_max(val, add)
{
	if (!history_undo && !history_redo)
		history_set_var(action_lib_pc_type_sprite_animation_speed_random_max, ptype_edit.sprite_animation_speed_random_max, ptype_edit.sprite_animation_speed_random_max * add + val, true)
	
	ptype_edit.sprite_animation_speed_random_max = ptype_edit.sprite_animation_speed_random_max * add + val
	tab_template_editor_particles_preview_restart()
}
