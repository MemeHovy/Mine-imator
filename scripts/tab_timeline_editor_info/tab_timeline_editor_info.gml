/// tab_properties_info()

function tab_timeline_editor_info()
{
	// Name
	tab_control_textfield()
	tab.info.tbx_name.text = tl_edit.name
	draw_textfield("timelineeditorname", dx, dy, dw, 24, tab.info.tbx_name, action_tl_name, string_remove_newline(tl_edit.display_name), "top")
	tab_next()
	
	if (tl_edit.type = e_temp_type.TEXT)
	{
		// Text
		tab_control_textfield(true, 76)
		tab.info.tbx_text.text = tl_edit.text
		draw_textfield("timelineeditortext", dx, dy, dw, 76, tab.info.tbx_text, action_tl_text, "", "top")
		tab_next()
	}
	
	// Type
	tab_control(28)
	draw_label_value(dx, dy, dw, 28, text_get("timelineeditortype"), string_remove_newline(tl_edit.type_name))
	tab_next()
	
	// Rotation point (Advanced mode only)
	if (tl_edit.value_type[e_value_type.ROT_POINT] && setting_advanced_mode)
	{
		tab_control_switch()
		draw_switch("timelineeditorrotpointcustom", dx, dy, tl_edit.rot_point_custom, action_tl_rotpoint_custom)
		tab_next()
		
		if (tl_edit.rot_point_custom)
		{
			var snapval, mul, def;
			snapval = (dragger_snap ? setting_snap_size_position : snap_min)
			mul = point3D_distance(tl_edit.world_pos, cam_from) / 500
			if (tl_edit.part_of = null && tl_edit.temp != null)
				def = tl_edit.temp.rot_point
			else
				def = point3D(0, 0, 0)
			
			axis_edit = X
			textfield_group_add("timelineeditorrotpointx", tl_edit.rot_point[axis_edit], def[axis_edit], action_tl_rotpoint, axis_edit, tab.info.tbx_rot_point_x)
			
			axis_edit = (setting_z_is_up ? Y : Z)
			textfield_group_add("timelineeditorrotpointy", tl_edit.rot_point[axis_edit], def[axis_edit], action_tl_rotpoint, axis_edit, tab.info.tbx_rot_point_y)
			
			axis_edit = (setting_z_is_up ? Z : Y)
			textfield_group_add("timelineeditorrotpointz", tl_edit.rot_point[axis_edit], def[axis_edit], action_tl_rotpoint, axis_edit, tab.info.tbx_rot_point_z)
			
			context_menu_group_temp = e_context_group.ROT_POINT
			
			tab_control_textfield_group(false)
			draw_textfield_group("timelineeditorrotpoint", dx, dy, dw, mul, -no_limit, no_limit, snapval, false, true, true)
			tab_next()
			
			context_menu_group_temp = null
		}
	}
	
	// Inverse kinematics
	if (tl_edit.type = e_tl_type.BODYPART && tl_edit.value_type[e_value_type.TRANSFORM_BEND] && tl_edit.model_part != null && tl_edit.model_part.bend_end_offset > 0)
	{
		tab_control_switch()
		draw_button_collapse("ik", collapse_map[?"ik"], null, true, "timelineeditorik", "timelineeditoriktip")
		tab_next()
		
		if (collapse_map[?"ik"])
		{
			tab_collapse_start()
			
			var text;
			
			// Target object
			if (tl_edit.ik_target != null)
				text = tl_edit.ik_target.display_name
			else
				text = text_get("listnone")
			
			tab_control_menu()
			draw_button_menu("timelineeditoriktarget", e_menu.TIMELINE, dx, dy, dw, 24, tl_edit.ik_target, text, action_tl_ik_target)
			tab_next()
			
			// Pole target object
			if (tl_edit.ik_pole_target != null)
				text = tl_edit.ik_pole_target.display_name
			else
				text = text_get("listnone")
			
			tab_control_menu()
			draw_button_menu("timelineeditorikpoletarget", e_menu.TIMELINE, dx, dy, dw, 24, tl_edit.ik_pole_target, text, action_tl_ik_pole_target, tl_edit.ik_target = null)
			tab_next()
			
			// Angle offset
			tab_control_dragger()
			draw_dragger("timelineeditorikangleoffset", dx, dy, dragger_width, tl_edit.ik_angle_offset, 0.1, -no_limit, no_limit, 0, snap_min, tab.info.tbx_ik_angle_offset, action_tl_ik_angle_offset, null, true, tl_edit.ik_target = null || tl_edit.ik_pole_target = null)
			tab_next()
			
			draw_tooltip_label("timelineeditorikinfo", icons.POSING, e_toast.INFO)
			
			tab_collapse_end()
		}
	}
}
