/// action_lib_pc_spawn_region_box_size(value, add)
/// @arg value
/// @arg add

function action_lib_pc_spawn_region_box_size(val, add)
{
	if (!history_undo && !history_redo)
		history_set_var(action_lib_pc_spawn_region_box_size, temp_edit.pc_spawn_region_box_size[axis_edit], temp_edit.pc_spawn_region_box_size[axis_edit] * add + val, true)
	
	temp_edit.pc_spawn_region_box_size[axis_edit] = temp_edit.pc_spawn_region_box_size[axis_edit] * add + val
}
