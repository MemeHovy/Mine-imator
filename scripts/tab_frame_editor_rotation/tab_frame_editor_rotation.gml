/// tab_frame_editor_rotation()

function tab_frame_editor_rotation()
{
	if (!tl_edit.value_type[e_value_type.TRANSFORM_ROT])
		return 0
	
	context_menu_group_temp = e_context_group.ROTATION
	tab_frame_editor_buttons()
	draw_label(text_get("frameeditorrotation"), dx, dy + 12, fa_left, fa_middle, c_text_secondary, a_text_secondary, font_label)
	dy += 26
	
	var snapval = (dragger_snap ? setting_snap_size_rotation : 0.1);
	
	// Wheels
	tab_control_wheel()
	axis_edit = X
	draw_wheel("frameeditorrotationxwheel", floor(dx + dw/6), dy + 24, c_control_red, tl_edit.value[e_value.ROT_X], -no_limit, no_limit, tl_edit.value_default[e_value.ROT_X], snapval, tab.transform.tbx_rot_x, action_tl_frame_rot)
	
	axis_edit = (setting_z_is_up ? Y : Z)
	draw_wheel("frameeditorrotationywheel", floor(dx + dw/2), dy + 24, c_control_green, tl_edit.value[e_value.ROT_X + axis_edit], -no_limit, no_limit, tl_edit.value_default[e_value.ROT_X + axis_edit], snapval, tab.transform.tbx_rot_y, action_tl_frame_rot)
	
	axis_edit = (setting_z_is_up ? Z : Y)
	draw_wheel("frameeditorrotationzwheel", floor(dx + dw - dw/6), dy + 24, c_control_blue, tl_edit.value[e_value.ROT_X + axis_edit], -no_limit, no_limit, tl_edit.value_default[e_value.ROT_X + axis_edit], snapval, tab.transform.tbx_rot_z, action_tl_frame_rot)
	tab_next()
	
	// Textboxes
	axis_edit = X
	textfield_group_add("frameeditorrotationx", tl_edit.value[e_value.ROT_X], tl_edit.value_default[e_value.ROT_X], action_tl_frame_rot, axis_edit, tab.transform.tbx_rot_x)
	
	axis_edit = (setting_z_is_up ? Y : Z)
	textfield_group_add("frameeditorrotationy", tl_edit.value[e_value.ROT_X + axis_edit], tl_edit.value_default[e_value.ROT_X + axis_edit], action_tl_frame_rot, axis_edit, tab.transform.tbx_rot_y)
	
	axis_edit = (setting_z_is_up ? Z : Y)
	textfield_group_add("frameeditorrotationz", tl_edit.value[e_value.ROT_X + axis_edit], tl_edit.value_default[e_value.ROT_X + axis_edit], action_tl_frame_rot, axis_edit, tab.transform.tbx_rot_z)
	
	tab_control_textfield(false)
	draw_textfield_group("frameeditorrotation", dx, dy, dw, 0.1, -no_limit, no_limit, snapval, false, true, true)
	tab_next()
	
	context_menu_group_temp = null
}
