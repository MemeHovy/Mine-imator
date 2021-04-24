/// render_high_indirect(export)
/// @arg export
/// @desc Ray traces shadow surf for light bounces, returns GI lighting buffer

function render_high_indirect(export)
{
	var samplestart, sampleend;
	
	// Set samples to setting
	if (!export)
	{
		if (render_samples >= setting_render_samples)
			return 0
		
		samplestart = render_samples
		sampleend = render_samples + 1
	}
	else
	{
		samplestart = 0
		sampleend = setting_render_samples
		render_samples = setting_render_samples
	}
	
	var shadowsurf, depthsurf, normalsurf, normalsurf2, diffusesurf, brightnesssurf;
	shadowsurf = render_surface_shadows
	
	render_surface_indirect = surface_require(render_surface_indirect, render_width, render_height)
	
	for (var s = samplestart; s < sampleend; s++)
	{
		random_set_seed(s)
		render_indirect_kernel = render_generate_sample_kernel(16)
		
		for (var i = 0; i < 16; i++)
			render_indirect_offset[i] = random_range(0, 1)
		
		// Render depth & normal data
		render_surface[1] = surface_require(render_surface[1], render_width, render_height, true, true)
		depthsurf = render_surface[1]
		
		render_surface[2] = surface_require(render_surface[2], render_width, render_height, true, true)
		normalsurf = render_surface[2]
		
		render_surface[3] = surface_require(render_surface[3], render_width, render_height, true, true)
		normalsurf2 = render_surface[3]
		
		render_surface[4] = surface_require(render_surface[4], render_width, render_height, true, true)
		diffusesurf = render_surface[4]
		
		render_surface[5] = surface_require(render_surface[5], render_width, render_height, true, true)
		brightnesssurf = render_surface[5]
		
		surface_set_target_ext(0, depthsurf)
		surface_set_target_ext(1, normalsurf)
		surface_set_target_ext(2, normalsurf2)
		surface_set_target_ext(3, brightnesssurf)
		{
			draw_clear_alpha(c_white, 0)
			render_world_start(5000)
			render_world(e_render_mode.HIGH_INDIRECT_DEPTH_NORMAL)
			render_world_done()
		}
		surface_reset_target()
		
		// Render diffuse color
		surface_set_target(diffusesurf)
		{
			// Background
			draw_clear_alpha(c_black, 0)
			render_world_background()
			
			// World
			render_world_start()
			render_world_sky()
			render_world(e_render_mode.COLOR_FOG)
			render_world_done()
		}
		surface_reset_target()
		
		// Ray trace GI
		surface_set_target(render_surface_indirect)
		{
			gpu_set_texrepeat(false)
		    draw_clear_alpha(c_black, 0)
			
		    render_shader_obj = shader_map[?shader_high_indirect]
		    with (render_shader_obj)
		    {
		        shader_set(shader)
		        shader_high_indirect_set(depthsurf, normalsurf, normalsurf2, diffusesurf, shadowsurf, brightnesssurf)
		    }
			
		    draw_blank(0, 0, render_width, render_height)
			
		    with (render_shader_obj)
		        shader_clear()
			gpu_set_texrepeat(true)
		}
		surface_reset_target()
		
		var exptemp, dectemp;
		render_surface_indirect_expo = surface_require(render_surface_indirect_expo, render_width, render_height)
		render_surface_indirect_dec = surface_require(render_surface_indirect_dec, render_width, render_height)
		render_surface[1] = surface_require(render_surface[1], render_width, render_height, true, true)
		render_surface[2] = surface_require(render_surface[2], render_width, render_height, true, true)
		exptemp = render_surface[1]
		dectemp = render_surface[2]
		
		// Draw temporary exponent surface
		surface_set_target(exptemp)
		{
			draw_clear_alpha(c_black, 1)
			draw_surface_exists(render_surface_indirect_expo, 0, 0)
			
			if (s = 0 || render_samples_clear)
				draw_clear_alpha(c_black, 1)
		}
		surface_reset_target()
		
		surface_set_target(dectemp)
		{
			draw_clear_alpha(c_black, 1)
			draw_surface_exists(render_surface_indirect_dec, 0, 0)
			
			if (s = 0 || render_samples_clear)
				draw_clear_alpha(c_black, 1)
		}
		surface_reset_target()
		
		// Add light shadow to buffer
		surface_set_target_ext(0, render_surface_indirect_expo)
		surface_set_target_ext(1, render_surface_indirect_dec)
		{
			render_shader_obj = shader_map[?shader_high_shadows_add]
			with (render_shader_obj)
			{
				shader_set(shader)
				shader_high_shadows_add_set(exptemp, dectemp)
			}
			draw_surface_exists(render_surface_indirect, 0, 0)
			with (render_shader_obj)
				shader_clear()
		}
		surface_reset_target()
	}
	
	surface_set_target(render_surface_indirect)
	{
		draw_clear_alpha(c_black, 1)
		gpu_set_blendmode(bm_add)
		
		render_shader_obj = shader_map[?shader_high_samples_unpack]
		with (render_shader_obj)
		{
			shader_set(shader)
			shader_high_samples_unpack_set(render_surface_indirect_expo, render_surface_indirect_dec, min(render_samples, app.setting_render_samples))
		}
		draw_blank(0, 0, render_width, render_height)
		with (render_shader_obj)
			shader_clear()
		
		gpu_set_blendmode(bm_normal)
	}
	surface_reset_target()
	
	#region Blur result (Using SSAO method)
	
	// Render depth & normal data
	render_surface[1] = surface_require(render_surface[1], render_width, render_height, true, true)
	depthsurf = render_surface[1]
	
	render_surface[2] = surface_require(render_surface[2], render_width, render_height, true, true)
	normalsurf = render_surface[2]
	
	surface_set_target_ext(0, depthsurf)
	surface_set_target_ext(1, normalsurf)
	{
		draw_clear_alpha(c_white, 0)
		render_world_start(5000)
		render_world(e_render_mode.HIGH_SSAO_DEPTH_NORMAL)
		render_world_done()
	}
	surface_reset_target()
	
	repeat (setting_render_indirect_blur_passes)
	{
		var gisurftemp;
		render_surface[3] = surface_require(render_surface[3], render_width, render_height)
		gisurftemp = render_surface[3]
		
		render_shader_obj = shader_map[?shader_high_ssao_blur]
		with (render_shader_obj)
			shader_set(shader)
		
		// Horizontal
		surface_set_target(gisurftemp)
		{
			with (render_shader_obj)
				shader_high_ssao_blur_set(depthsurf, normalsurf, 1, 0)
			draw_surface_exists(render_surface_indirect, 0, 0)
		}
		surface_reset_target()
		
		// Vertical
		surface_set_target(render_surface_indirect)
		{
			with (render_shader_obj)
				shader_high_ssao_blur_set(depthsurf, normalsurf, 0, 1)
			draw_surface_exists(gisurftemp, 0, 0)
		}
		surface_reset_target()
		
		with (render_shader_obj)
			shader_clear()
	}
	gpu_set_texrepeat(true)
	
	#endregion
	
	if (export)
	{
		surface_free(render_surface_indirect_expo)
		surface_free(render_surface_indirect_dec)
	}
}
