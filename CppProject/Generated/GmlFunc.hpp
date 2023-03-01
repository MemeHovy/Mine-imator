/*
	NOTE:
	This file was autogenerated by CppGen, changes may be overwritten and forever lost!
	Modify at your own risk!
	
	[ Generated on 2023.01.29 11:37:00 ]
*/

#pragma once
#include "Asset/Scope.hpp"

#define withOne(type, id, otherId) \
	if (IntType _withSelfId = id) \
	if (IntType _withOtherId = otherId) \
	for (Scope<type> self(_withSelfId, _withOtherId); self.IsValid(); self.Clear())

#define withAll(type, otherId) \
	if (IntType _withOtherId = otherId) \
	for (Scope<type> self(Object::GetAll(ID_##type), _withOtherId); self.IsValid(); self.NextObject())

namespace CppProject
{
	#define audio_3d IntType(2)
	#define audio_mono IntType(0)
	#define audio_stereo IntType(1)
	#define bm_add IntType(1)
	#define bm_dest_alpha IntType(7)
	#define bm_dest_color IntType(9)
	#define bm_inv_dest_alpha IntType(8)
	#define bm_inv_dest_color IntType(10)
	#define bm_inv_src_alpha IntType(6)
	#define bm_inv_src_color IntType(4)
	#define bm_max IntType(4)
	#define bm_normal IntType(0)
	#define bm_one IntType(2)
	#define bm_src_alpha IntType(5)
	#define bm_src_alpha_sat IntType(11)
	#define bm_src_color IntType(3)
	#define bm_subtract IntType(3)
	#define bm_zero IntType(1)
	#define buffer_f32 IntType(8)
	#define buffer_f64 IntType(9)
	#define buffer_fixed IntType(0)
	#define buffer_grow IntType(1)
	#define buffer_s16 IntType(4)
	#define buffer_s32 IntType(6)
	#define buffer_s8 IntType(2)
	#define buffer_seek_end IntType(2)
	#define buffer_seek_relative IntType(1)
	#define buffer_seek_start IntType(0)
	#define buffer_u16 IntType(3)
	#define buffer_u32 IntType(5)
	#define buffer_u8 IntType(1)
	#define c_aqua IntType(16776960)
	#define c_black IntType(0)
	#define c_blue IntType(16711680)
	#define c_dkgray IntType(4210752)
	#define c_dkgrey IntType(4210752)
	#define c_fuchsia IntType(16711935)
	#define c_gray IntType(8421504)
	#define c_green IntType(32768)
	#define c_grey IntType(8421504)
	#define c_lime IntType(65280)
	#define c_ltgray IntType(12632256)
	#define c_ltgrey IntType(12632256)
	#define c_maroon IntType(128)
	#define c_navy IntType(8388608)
	#define c_olive IntType(32896)
	#define c_orange IntType(4235519)
	#define c_purple IntType(8388736)
	#define c_red IntType(255)
	#define c_silver IntType(12632256)
	#define c_teal IntType(8421376)
	#define c_white IntType(16777215)
	#define c_yellow IntType(65535)
	#define cr_beam IntType(-4)
	#define cr_default IntType(0)
	#define cr_drag IntType(-10)
	#define cr_handpoint IntType(-21)
	#define cr_none IntType(-1)
	#define cr_size_all IntType(-22)
	#define cr_size_nesw IntType(-6)
	#define cr_size_ns IntType(-7)
	#define cr_size_nwse IntType(-8)
	#define cr_size_we IntType(-9)
	#define cull_counterclockwise IntType(2)
	#define cull_noculling IntType(0)
	#define dll_cdecl IntType(0)
	#define ds_type_grid IntType(4)
	#define ds_type_list IntType(2)
	#define ds_type_map IntType(1)
	#define ds_type_priority IntType(6)
	#define ds_type_queue IntType(5)
	#define ds_type_stack IntType(3)
	#define fa_bottom IntType(2)
	#define fa_center IntType(1)
	#define fa_left IntType(0)
	#define fa_middle IntType(1)
	#define fa_right IntType(2)
	#define fa_top IntType(0)
	#define matrix_projection IntType(1)
	#define matrix_view IntType(0)
	#define matrix_world IntType(2)
	#define mb_left IntType(1)
	#define mb_middle IntType(3)
	#define mb_right IntType(2)
	#define mip_off IntType(0)
	#define mip_on IntType(1)
	#define pi_ 3.14159265
	#define pr_pointlist IntType(1)
	#define pr_linelist IntType(2)
	#define pr_linestrip IntType(3)
	#define pr_trianglefan IntType(6)
	#define pr_trianglelist IntType(4)
	#define pr_trianglestrip IntType(5)
	#define tf_anisotropic IntType(2)
	#define tf_linear IntType(1)
	#define tf_point IntType(0)
	#define ty_real IntType(0)
	#define ty_string IntType(1)
	#define vertex_type_float4 IntType(4)
	#define vertex_usage_texcoord IntType(4)
	#define vk_add IntType(107)
	#define vk_alt IntType(18)
	#define vk_anykey IntType(1)
	#define vk_backspace IntType(8)
	#define vk_control IntType(17)
	#define vk_decimal IntType(110)
	#define vk_delete IntType(46)
	#define vk_divide IntType(111)
	#define vk_down IntType(40)
	#define vk_end IntType(35)
	#define vk_enter IntType(13)
	#define vk_escape IntType(27)
	#define vk_f1 IntType(112)
	#define vk_f10 IntType(121)
	#define vk_f11 IntType(122)
	#define vk_f12 IntType(123)
	#define vk_f2 IntType(113)
	#define vk_f3 IntType(114)
	#define vk_f4 IntType(115)
	#define vk_f5 IntType(116)
	#define vk_f6 IntType(117)
	#define vk_f7 IntType(118)
	#define vk_f8 IntType(119)
	#define vk_f9 IntType(120)
	#define vk_home IntType(36)
	#define vk_insert IntType(45)
	#define vk_lalt IntType(164)
	#define vk_lcontrol IntType(162)
	#define vk_left IntType(37)
	#define vk_lshift IntType(160)
	#define vk_multiply IntType(106)
	#define vk_nokey IntType(0)
	#define vk_numpad0 IntType(96)
	#define vk_numpad1 IntType(97)
	#define vk_numpad2 IntType(98)
	#define vk_numpad3 IntType(99)
	#define vk_numpad4 IntType(100)
	#define vk_numpad5 IntType(101)
	#define vk_numpad6 IntType(102)
	#define vk_numpad7 IntType(103)
	#define vk_numpad8 IntType(104)
	#define vk_numpad9 IntType(105)
	#define vk_pagedown IntType(34)
	#define vk_pageup IntType(33)
	#define vk_pause IntType(19)
	#define vk_printscreen IntType(44)
	#define vk_ralt IntType(165)
	#define vk_rcontrol IntType(163)
	#define vk_right IntType(39)
	#define vk_rshift IntType(161)
	#define vk_shift IntType(16)
	#define vk_space IntType(32)
	#define vk_subtract IntType(109)
	#define vk_tab IntType(9)
	#define vk_up IntType(38)
	
	struct gmlGlobal
	{
		static IntType application_surface;
		static IntType async_load;
		static IntType current_time;
		static IntType delta_time;
		static IntType fps_real;
		static IntType fps;
		static StringType game_save_id;
		static StringType GM_runtime_version;
		static IntType instance_count;
		static IntType keyboard_lastkey;
		static StringType keyboard_string;
		static IntType mouse_x;
		static IntType mouse_y;
		static IntType os_version;
		static IntType room_speed;
		static StringType working_directory;
	};
	
	RealType abs(RealType);
	RealType arccos(RealType);
	RealType arcsin(RealType);
	RealType arctan(RealType);
	RealType arctan2(RealType, RealType);
	void array_copy(VarType, IntType, VarType, IntType, IntType);
	ArrType array_create(VarArgs args = VarArgs());
	IntType array_equals(VarType, VarType);
	IntType array_length(VarType);
	VarType asset_get_index(StringType);
	IntType audio_create_buffer_sound(IntType, IntType, IntType, IntType, IntType, IntType);
	void audio_free_buffer_sound(IntType);
	BoolType audio_is_paused(IntType);
	BoolType audio_is_playing(IntType);
	void audio_pause_sound(IntType);
	IntType audio_play_sound(IntType, IntType, BoolType);
	void audio_resume_sound(IntType);
	void audio_sound_gain(IntType, RealType, RealType);
	RealType audio_sound_get_track_position(IntType);
	void audio_sound_set_track_position(IntType, RealType);
	void audio_stop_all();
	void audio_stop_sound(IntType);
	StringType base64_decode(StringType);
	void buffer_copy(IntType, IntType, IntType, IntType, IntType);
	IntType buffer_create(IntType, IntType, IntType);
	IntType buffer_create_from_vertex_buffer(IntType, IntType, IntType);
	void buffer_delete(IntType);
	void buffer_fill(IntType, IntType, IntType, VarType, IntType);
	IntType buffer_get_size(IntType);
	void buffer_get_surface(IntType, IntType, IntType);
	IntType buffer_load(StringType);
	VarType buffer_peek(IntType, IntType, IntType);
	void buffer_poke(IntType, IntType, VarType, IntType);
	VarType buffer_read(IntType, IntType);
	void buffer_resize(IntType, IntType);
	void buffer_save(IntType, StringType);
	void buffer_seek(IntType, IntType, IntType);
	IntType buffer_tell(IntType);
	IntType buffer_write(IntType, IntType, VarType);
	void camera_apply(IntType);
	IntType camera_create();
	void camera_set_proj_mat(IntType, MatrixType);
	void camera_set_view_mat(IntType, MatrixType);
	void camera_set_view_pos(IntType, RealType, RealType);
	void camera_set_view_size(IntType, RealType, RealType);
	RealType ceil(RealType);
	VarType choose(VarArgs args = VarArgs());
	StringType chr(IntType);
	RealType clamp(RealType, RealType, RealType);
	StringType clipboard_get_text();
	IntType clipboard_has_text();
	void clipboard_set_text(StringType);
	BoolType code_is_compiled();
	IntType color_get_blue(IntType);
	IntType color_get_green(IntType);
	IntType color_get_hue(IntType);
	IntType color_get_red(IntType);
	IntType color_get_saturation(IntType);
	IntType color_get_value(IntType);
	RealType cos(RealType);
	IntType current_time();
	RealType date_current_datetime();
	RealType date_day_span(RealType, RealType);
	RealType date_get_day(RealType);
	RealType date_get_month(RealType);
	RealType date_get_week(RealType);
	RealType date_get_year(RealType);
	RealType date_hour_span(RealType, RealType);
	RealType date_minute_span(RealType, RealType);
	RealType date_second_span(RealType, RealType);
	StringType date_time_string(RealType);
	RealType date_week_span(RealType, RealType);
	RealType dcos(RealType);
	RealType degtorad(RealType);
	IntType display_get_dpi_x();
	IntType display_get_dpi_y();
	IntType display_mouse_get_x();
	IntType display_mouse_get_y();
	void display_mouse_set(IntType, IntType);
	IntType display_reset(IntType, IntType);
	void draw_clear_alpha(IntType, RealType);
	void draw_clear(IntType);
	RealType draw_get_alpha();
	IntType draw_get_color();
	IntType draw_get_font();
	void draw_line(IntType, IntType, IntType, IntType);
	void draw_line_color(IntType, IntType, IntType, IntType, IntType, IntType);
	void draw_line_width(IntType, IntType, IntType, IntType, IntType);
	void draw_line_width_color(IntType, IntType, IntType, IntType, IntType, IntType, IntType);
	void draw_point_color(IntType, IntType, IntType);
	void draw_primitive_begin(IntType);
	void draw_primitive_end();
	void draw_rectangle(IntType, IntType, IntType, IntType, BoolType);
	void draw_set_alpha(RealType);
	void draw_set_color(IntType);
	void draw_set_font(IntType);
	void draw_set_halign(IntType);
	void draw_set_valign(IntType);
	void draw_sprite_ext(IntType, IntType, IntType, IntType, RealType, RealType, RealType, IntType, RealType);
	void draw_sprite_general(IntType, IntType, IntType, IntType, IntType, IntType, IntType, IntType, RealType, RealType, RealType, IntType, IntType, IntType, IntType, RealType);
	void draw_sprite_part_ext(IntType, IntType, IntType, IntType, IntType, IntType, IntType, IntType, RealType, RealType, IntType, RealType);
	void draw_sprite(IntType, IntType, IntType, IntType);
	void draw_surface_ext(IntType, IntType, IntType, RealType, RealType, RealType, IntType, RealType);
	void draw_surface(IntType, IntType, IntType);
	void draw_text_ext(IntType, IntType, StringType, IntType, IntType);
	void draw_text_transformed(IntType, IntType, StringType, RealType, RealType, RealType);
	void draw_text(IntType, IntType, StringType);
	void draw_vertex_color(IntType, IntType, IntType, RealType);
	void draw_vertex_texture_color(IntType, IntType, RealType, RealType, IntType, RealType);
	void draw_vertex_texture(IntType, IntType, RealType, RealType);
	void draw_vertex(IntType, IntType);
	BoolType ds_exists(VarType, IntType);
	void ds_grid_clear(IntType, VarType);
	IntType ds_grid_create(IntType, IntType);
	void ds_grid_destroy(IntType);
	VarType ds_grid_get(IntType, IntType, IntType);
	void ds_grid_set(IntType, IntType, IntType, VarType);
	void ds_list_add(VarArgs args = VarArgs());
	void ds_list_clear(IntType);
	void ds_list_copy(IntType, IntType);
	IntType ds_list_create();
	void ds_list_delete(IntType, IntType);
	void ds_list_destroy(IntType);
	BoolType ds_list_empty(IntType);
	IntType ds_list_find_index(IntType, VarType);
	VarType ds_list_find_value(IntType, IntType);
	void ds_list_insert(IntType, IntType, VarType);
	IntType ds_list_mark_as_list(IntType, IntType);
	IntType ds_list_mark_as_map(IntType, IntType);
	IntType ds_list_size(IntType);
	void ds_list_sort(IntType, BoolType);
	void ds_map_add_list(IntType, VarType, IntType);
	void ds_map_add_map(IntType, VarType, IntType);
	BoolType ds_map_add(IntType, VarType, VarType);
	void ds_map_clear(IntType);
	void ds_map_copy(IntType, IntType);
	IntType ds_map_create();
	void ds_map_delete(IntType, VarType);
	void ds_map_destroy(IntType);
	BoolType ds_map_exists(IntType, VarType);
	VarType ds_map_find_first(IntType);
	VarType ds_map_find_next(IntType, VarType);
	VarType ds_map_find_value(IntType, VarType);
	IntType ds_map_size(IntType);
	void ds_priority_add(IntType, VarType, IntType);
	IntType ds_priority_create();
	VarType ds_priority_delete_max(IntType);
	VarType ds_priority_find_max(IntType);
	IntType ds_priority_size(IntType);
	IntType ds_stack_create();
	void ds_stack_destroy(IntType);
	BoolType ds_stack_empty(IntType);
	VarType ds_stack_pop(IntType);
	void ds_stack_push(VarArgs args = VarArgs());
	VarType ds_stack_top(IntType);
	RealType dsin(RealType);
	StringType environment_get_variable(StringType);
	VarType external_call(VarArgs args = VarArgs());
	IntType external_define(VarArgs args = VarArgs());
	BoolType file_delete(StringType);
	BoolType file_exists(StringType);
	void file_find_close();
	StringType file_find_first(StringType, IntType);
	StringType file_find_next();
	BoolType file_rename(StringType, StringType);
	void file_text_close(IntType);
	BoolType file_text_eof(IntType);
	IntType file_text_open_append(StringType);
	IntType file_text_open_read(StringType);
	IntType file_text_open_write(StringType);
	StringType file_text_read_string(IntType);
	StringType file_text_readln(IntType);
	IntType file_text_write_string(IntType, StringType);
	IntType file_text_writeln(IntType);
	StringType filename_change_ext(StringType, StringType);
	StringType filename_dir(StringType);
	StringType filename_ext(StringType);
	StringType filename_name(StringType);
	StringType filename_path(StringType);
	RealType floor(RealType);
	void font_add_enable_aa(BoolType);
	IntType font_add_sprite_ext(IntType, StringType, BoolType, IntType);
	IntType font_add(StringType, IntType, BoolType, BoolType, IntType, IntType);
	void font_delete(IntType);
	BoolType font_exists(IntType);
	RealType frac(RealType);
	void game_end();
	void gc_collect();
	void gc_target_frame_time(IntType);
	StringType get_open_filename_ext(StringType, StringType, StringType, StringType);
	StringType get_save_filename_ext(StringType, StringType, StringType, StringType);
	void gml_pragma(VarArgs args = VarArgs());
	void gml_release_mode(BoolType);
	IntType gpu_get_blendmode();
	IntType gpu_get_cullmode();
	BoolType gpu_get_tex_filter();
	IntType gpu_get_tex_mip_bias();
	IntType gpu_get_tex_mip_enable();
	BoolType gpu_get_texfilter_ext(IntType);
	void gpu_set_alphatestenable(BoolType);
	void gpu_set_alphatestref(IntType);
	void gpu_set_blendenable(BoolType);
	void gpu_set_blendmode_ext_sepalpha(IntType, IntType, IntType, IntType);
	void gpu_set_blendmode_ext(IntType, IntType);
	void gpu_set_blendmode(IntType);
	void gpu_set_cullmode(IntType);
	void gpu_set_tex_filter(BoolType);
	void gpu_set_tex_max_mip(IntType);
	void gpu_set_tex_mip_bias(IntType);
	void gpu_set_tex_mip_enable(IntType);
	void gpu_set_tex_mip_filter_ext(IntType, IntType);
	void gpu_set_tex_mip_filter(IntType);
	void gpu_set_tex_repeat(BoolType);
	void gpu_set_texfilter_ext(IntType, BoolType);
	void gpu_set_tex_filter_ext(IntType, BoolType);
	void gpu_set_texfilter(BoolType);
	void gpu_set_texrepeat_ext(IntType, BoolType);
	void gpu_set_texrepeat(BoolType);
	void gpu_set_ztestenable(BoolType);
	void gpu_set_zwriteenable(BoolType);
	IntType http_get_file(StringType, StringType);
	IntType http_get(StringType);
	void instance_activate_object(VarType);
	VarType instance_create_depth(IntType, IntType, IntType, VarType);
	void instance_deactivate_object(VarType);
	void instance_destroy(ScopeAny, VarArgs args = VarArgs());
	BoolType instance_exists(VarType);
	IntType instance_number(VarType);
	IntType irandom_range(IntType, IntType);
	IntType irandom(IntType);
	BoolType is_array(VarType);
	BoolType is_bool(VarType);
	BoolType is_int32(VarType);
	BoolType is_int64(VarType);
	BoolType is_real(VarType);
	BoolType is_string(VarType);
	BoolType is_undefined(VarType);
	IntType json_decode(StringType);
	BoolType keyboard_check_direct(IntType);
	BoolType keyboard_check_pressed(IntType);
	BoolType keyboard_check_released(IntType);
	BoolType keyboard_check(IntType);
	void keyboard_clear(IntType);
	RealType lengthdir_x(RealType, RealType);
	RealType lengthdir_y(RealType, RealType);
	RealType lerp(RealType, RealType, RealType);
	RealType log2(RealType);
	IntType make_color_hsv(IntType, IntType, IntType);
	IntType make_color_rgb(IntType, IntType, IntType);
	MatrixType matrix_build_lookat(RealType, RealType, RealType, RealType, RealType, RealType, RealType, RealType, RealType);
	MatrixType matrix_build_projection_ortho(RealType, RealType, RealType, RealType);
	MatrixType matrix_build_projection_perspective_fov(RealType, RealType, RealType, RealType);
	MatrixType matrix_build(RealType, RealType, RealType, RealType, RealType, RealType, RealType, RealType, RealType);
	MatrixType matrix_get(IntType);
	MatrixType matrix_multiply(MatrixType, MatrixType);
	void matrix_set(IntType, MatrixType);
	VecType matrix_transform_vertex(MatrixType, RealType, RealType, RealType);
	RealType max(VarArgs args = VarArgs());
	IntType merge_color(IntType, IntType, RealType);
	RealType min(VarArgs args = VarArgs());
	BoolType mouse_check_button(IntType);
	BoolType mouse_clear(IntType);
	BoolType mouse_wheel_down();
	BoolType mouse_wheel_up();
	IntType ord(StringType);
	IntType os_get_info();
	StringType os_get_language();
	StringType os_get_region();
	BoolType os_is_network_connected();
	RealType point_direction(RealType, RealType, RealType, RealType);
	RealType point_distance_3d(RealType, RealType, RealType, RealType, RealType, RealType);
	RealType point_distance(RealType, RealType, RealType, RealType);
	BoolType point_in_triangle(RealType, RealType, RealType, RealType, RealType, RealType, RealType, RealType);
	RealType power(RealType, RealType);
	RealType radtodeg(RealType);
	IntType random_get_seed();
	RealType random_range(RealType, RealType);
	void random_set_seed(IntType);
	RealType random(RealType);
	void randomize();
	RealType real(VarType);
	RealType round(RealType);
	VarType script_execute(ScopeAny, VarArgs args = VarArgs());
	BoolType script_exists(IntType);
	StringType script_get_name(IntType);
	IntType shader_get_sampler_index(IntType, StringType);
	IntType shader_get_uniform(IntType, StringType);
	BoolType shader_is_compiled(IntType);
	void shader_reset();
	void shader_set_uniform_f_array(IntType, VarType);
	void shader_set_uniform_f(VarArgs args = VarArgs());
	void shader_set_uniform_i_array(IntType, ArrType);
	void shader_set_uniform_i(VarArgs args = VarArgs());
	void shader_set(IntType);
	BoolType shaders_are_supported();
	void show_debug_message(StringType);
	void show_message(StringType);
	BoolType show_question(StringType);
	RealType sign(RealType);
	RealType sin(RealType);
	IntType sprite_add(StringType, IntType, BoolType, BoolType, IntType, IntType);
	IntType sprite_create_from_surface(IntType, IntType, IntType, IntType, IntType, BoolType, BoolType, IntType, IntType);
	void sprite_delete(IntType);
	IntType sprite_duplicate(IntType);
	BoolType sprite_exists(IntType);
	IntType sprite_get_height(IntType);
	IntType sprite_get_number(IntType);
	IntType sprite_get_texture(IntType, IntType);
	IntType sprite_get_width(IntType);
	void sprite_set_offset(IntType, IntType, IntType);
	RealType sqr(RealType);
	RealType sqrt(RealType);
	StringType string_char_at(StringType, IntType);
	StringType string_copy(StringType, IntType, IntType);
	IntType string_count(StringType, StringType);
	StringType string_delete(StringType, IntType, IntType);
	StringType string_digits(StringType);
	StringType string_format(RealType, IntType, IntType);
	IntType string_height_ext(StringType, IntType, IntType);
	IntType string_height(StringType);
	StringType string_insert(StringType, StringType, IntType);
	IntType string_length(StringType);
	StringType string_lower(StringType);
	IntType string_pos(StringType, StringType);
	StringType string_repeat(StringType, IntType);
	StringType string_replace_all(StringType, StringType, StringType);
	StringType string_replace(StringType, StringType, StringType);
	StringType string_upper(StringType);
	IntType string_width(StringType);
	StringType string(VarType);
	void surface_copy(IntType, IntType, IntType, IntType);
	IntType surface_create(IntType, IntType);
	BoolType surface_exists(IntType);
	void surface_free(IntType);
	IntType surface_get_height(IntType);
	IntType surface_get_texture(IntType);
	IntType surface_get_width(IntType);
	IntType surface_getpixel(IntType, IntType, IntType);
	void surface_reset_target();
	void surface_resize(IntType, IntType, IntType);
	void surface_save(IntType, StringType);
	IntType surface_set_target_ext(IntType, IntType);
	IntType surface_set_target(IntType);
	void texture_set_stage(IntType, IntType);
	void vertex_begin(IntType, IntType);
	void vertex_color(IntType, IntType, RealType);
	IntType vertex_create_buffer();
	IntType vertex_create_buffer_from_buffer(IntType, IntType);
	void vertex_delete_buffer(IntType);
	void vertex_end(IntType);
	void vertex_float3(IntType, RealType, RealType, RealType);
	void vertex_float4(IntType, RealType, RealType, RealType, RealType);
	void vertex_format_add_colour();
	void vertex_format_add_custom(IntType, IntType);
	void vertex_format_add_normal();
	void vertex_format_add_position_3d();
	void vertex_format_add_texcoord();
	void vertex_format_begin();
	IntType vertex_format_end();
	void vertex_freeze(IntType);
	IntType vertex_get_number(IntType);
	void vertex_normal(IntType, RealType, RealType, RealType);
	void vertex_position_3d(IntType, RealType, RealType, RealType);
	void vertex_submit(IntType, IntType, IntType);
	void vertex_texcoord(IntType, RealType, RealType);
	void view_set_camera(IntType, IntType);
	RealType view_set_hport(IntType, IntType);
	RealType view_set_wport(IntType, IntType);
	IntType window_get_height();
	IntType window_get_width();
	IntType window_get_x();
	IntType window_get_y();
	StringType window_handle();
	void window_mouse_set(IntType, IntType);
	void window_set_caption(StringType);
	void window_set_cursor(IntType);
	void window_set_min_height(IntType);
	void window_set_min_width(IntType);
	void window_set_rectangle(IntType, IntType, IntType, IntType);
	void window_set_size(IntType, IntType);
}
