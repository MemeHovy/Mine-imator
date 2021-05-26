/// shader_high_subsurface_scatter_set(ssssurf, rangesurf, depthsurf, diffusesurf, directsurf, direction)
/// @arg ssssurf
/// @arg rangesurf
/// @arg depthsurf
/// @arg directsurf
/// @arg direction

function shader_high_subsurface_scatter_set(ssssurf, rangesurf, depthsurf, directsurf, dir)
{
	texture_set_stage(sampler_map[?"uSSSBuffer"], surface_get_texture(ssssurf))
	gpu_set_texfilter_ext(sampler_map[?"uSSSBuffer"], false)
	
	texture_set_stage(sampler_map[?"uSSSRangeBuffer"], surface_get_texture(rangesurf))
	gpu_set_texfilter_ext(sampler_map[?"uSSSRangeBuffer"], false)
	
	texture_set_stage(sampler_map[?"uDepthBuffer"], surface_get_texture(depthsurf))
	gpu_set_texfilter_ext(sampler_map[?"uDepthBuffer"], false)
	
	texture_set_stage(sampler_map[?"uDirect"], surface_get_texture(directsurf))
	gpu_set_texfilter_ext(sampler_map[?"uDirect"], false)
	
	texture_set_stage(sampler_map[?"uNoiseBuffer"], surface_get_texture(render_sample_noise_surf))
	gpu_set_texfilter_ext(sampler_map[?"uNoiseBuffer"], false)
	
	render_set_uniform("uNoiseSize", render_sample_noise_size)
	render_set_uniform("uProjMatrix", proj_matrix)
	render_set_uniform("uProjMatrixInv", matrix_inverse(proj_matrix))
	render_set_uniform_vec2("uScreenSize", render_width, render_height)
	render_set_uniform("uNear", cam_near)
	render_set_uniform("uFar", cam_far)
	
	render_set_uniform_int("uSamples", render_subsurface_size)
	render_set_uniform("uKernel", render_subsurface_kernel)
	render_set_uniform_vec2("uDirection", dir[X], dir[Y])
	render_set_uniform("uJitterThreshold", app.project_render_subsurface_jitter)
}
