/// shader_draw_texture_set()

var uTexture = shader_get_sampler_index(shader_draw_texture, "uTexture");

shader_set(shader_draw_texture)

shader_set_texture(uTexture, shader_texture)
