/// project_reset()

function project_reset()
{
	log("Resetting project")
	
	project_reset_backup()
	history_clear()
	
	temp_edit = null
	res_edit = null
	tl_edit = null
	tl_edit_amount = 0
	
	lib_preview.update = true
	res_preview.update = true
	
	project_file = ""
	project_folder = ""
	project_changed = false
	project_name = ""
	project_author = ""
	project_description = ""
	project_video_width = 1280
	project_video_height = 720
	project_video_template = find_videotemplate(project_video_width, project_video_height)
	project_video_keep_aspect_ratio = true
	project_tempo = 24
	project_grid_rows = 3
	project_grid_columns = 3
	
	camera_work_reset()
	
	log("Destroying instances")
	
	with (obj_template)
		instance_destroy()
	
	with (obj_timeline)
		if (!delete_ready)
			tl_remove_clean()
	
	with (obj_timeline)
		instance_destroy()
	
	with (obj_resource)
		if (id != mc_res)
			instance_destroy()
	
	with (obj_keyframe)
		instance_destroy()
	
	with (obj_marker)
		instance_destroy()
	
	with (mc_res)
		count = 0
	
	background_image_show = false
	background_image = null
	background_image_type = "image"
	background_image_stretch = true
	background_image_box_mapped = false
	background_image_rotation = 0
	
	background_sky_sun_tex = mc_res
	background_sky_sun_tex.count++
	background_sky_moon_tex = mc_res
	background_sky_moon_tex.count++
	background_sky_moon_phase = 0
	
	background_sky_time = -45
	background_sky_rotation = 0
	background_sunlight_range = 2000
	background_sunlight_follow = false
	background_sunlight_strength = 0
	background_sunlight_angle = .526
	background_twilight = true
	background_desaturate_night = false
	background_desaturate_night_amount = 0
	
	background_sky_clouds_show = true
	background_sky_clouds_update = false
	background_sky_clouds_tex = mc_res
	background_sky_clouds_tex.count++
	background_sky_clouds_mode = "normal"
	background_sky_clouds_speed = 1
	background_sky_clouds_height = 1024
	background_sky_clouds_size = 1536
	background_sky_clouds_thickness = 64
	background_sky_clouds_offset = 0
	background_sky_update_clouds()
	
	background_ground_show = true
	background_ground_tex = mc_res
	background_ground_tex.count++
	background_ground_name = default_ground
	background_ground_slot = ds_list_find_index(mc_assets.block_texture_list, background_ground_name)
	background_ground_slot_prev = null
	background_ground_tex_prev = null
	background_ground_update_texture()
	
	background_biome = biome_list[|2]
	background_grass_color = c_plains_biome_grass
	background_foliage_color = c_plains_biome_foliage
	background_water_color = c_plains_biome_water
	background_leaves_oak_color = c_plains_biome_foliage
	background_leaves_spruce_color = c_plains_biome_foliage_2
	background_leaves_birch_color = c_plains_biome_foliage_2
	background_leaves_jungle_color = c_plains_biome_foliage
	background_leaves_acacia_color = c_plains_biome_foliage
	background_leaves_dark_oak_color = c_plains_biome_foliage
	
	instance_activate_object(obj_biome)
	with (obj_biome)
	{
		if (biome_base = null)
			selected_variant = 0
	}
	instance_deactivate_object(obj_biome)
	
	with (mc_res)
		res_update_colors()
	
	background_sky_color = c_sky
	background_sky_clouds_color = c_clouds
	background_sunlight_color = c_sunlight
	background_ambient_color = c_ambient
	background_night_color = c_night
	
	background_volumetric_fog = false
	background_volumetric_fog_rays = false
	background_volumetric_fog_scatter = 0
	background_volumetric_fog_density = 0.2
	background_volumetric_fog_color = c_white
	background_volumetric_fog_height = 200
	background_volumetric_fog_height_fade = 100
	background_volumetric_fog_noise_scale = 16
	background_volumetric_fog_noise_contrast = 0
	background_volumetric_fog_brightness = 0
	background_volumetric_fog_wind = 1
	
	background_fog_show = true
	background_fog_sky = true
	background_fog_color_custom = 0
	background_fog_color = c_sky
	background_fog_object_color_custom = 0
	background_fog_object_color = c_sky
	background_fog_distance = 10000
	background_fog_size = 2000
	background_fog_height = 1250
	
	background_wind = true
	background_wind_speed = 0.1
	background_wind_strength = 0.5
	
	background_wind_direction = 45
	background_wind_directional_speed = 0.2
	background_wind_directional_strength = 1.5
	
	background_opaque_leaves = false
	background_texture_animation_speed = 0.25
	
	background_sunlight_color_final = c_black
	background_ambient_color_final = c_black
	background_fog_color_final = c_black
	background_night_alpha = 0
	background_sunset_alpha = 0
	background_sunrise_alpha = 0
	
	background_time = 0
	background_time_prev = 0
	
	timeline.hor_scroll.value = 0
	timeline.ver_scroll.value = 0
	
	action_tl_play_break()
	timeline_repeat = false
	timeline_marker = 0
	timeline_marker_previous = 0
	timeline_length = 0
	timeline_zoom = 16
	timeline_zoom_goal = 16
	timeline_camera = null
	copy_kf_amount = 0
	
	timeline_intervals_show = false
	timeline_interval_size = 24
	timeline_interval_offset = 0
	timeline_show_markers = true
	timeline_hide_color_tag = array_create(9, false)
	
	ds_list_clear(tree_list)
	ds_list_clear(tree_visible_list)
	app_update_tl_edit()
	
	for (var v = 0; v < e_value.amount; v++)
		value_default[v] = tl_value_default(v)
	
	log("Project resetted")
}
