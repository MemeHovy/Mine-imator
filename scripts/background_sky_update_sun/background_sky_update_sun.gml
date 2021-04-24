/// background_sky_update_sun()

function background_sky_update_sun()
{
	var range = world_size/8;
	
	background_light_data[0] = lengthdir_x(range, background_sky_rotation - 90) * lengthdir_x(1, background_sky_time + 90) + cam_from[X] * background_sunlight_follow
	background_light_data[1] = lengthdir_y(range, background_sky_rotation - 90) * lengthdir_x(1, background_sky_time + 90) + cam_from[Y] * background_sunlight_follow
	background_light_data[2] = lengthdir_z(range, background_sky_time + 90)
	
	if (background_sky_time = 0)
		background_light_data[0] += 0.1
	
	background_light_data[3] = range / 2
	background_light_data[4] = color_get_red(background_sunlight_color_final) / 255
	background_light_data[5] = color_get_green(background_sunlight_color_final) / 255
	background_light_data[6] = color_get_blue(background_sunlight_color_final) / 255
	background_light_data[7] = range * 2
}
