/// action_tl_frame_cam_dof_fade_size(value, add)
/// @arg value
/// @arg add

function action_tl_frame_cam_dof_fade_size(val, add)
{
	tl_value_set_start(action_tl_frame_cam_dof_fade_size, true)
	tl_value_set(e_value.CAM_DOF_FADE_SIZE, val, add)
	tl_value_set_done()
}
