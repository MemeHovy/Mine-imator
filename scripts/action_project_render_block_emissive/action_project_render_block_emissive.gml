/// action_project_render_block_emissive(value, add)
/// @arg value
/// @arg add

function action_project_render_block_emissive(val, add)
{
	if (!history_undo && !history_redo)
		history_set_var(action_project_render_block_emissive, project_render_block_emissive, project_render_block_emissive * add + val / 100, 1)
	else
		val *= 100
	
	project_render_block_emissive = project_render_block_emissive * add + val / 100
	render_samples = -1
}
