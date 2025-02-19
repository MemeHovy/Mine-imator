/*
	NOTE:
	This file was autogenerated by CppGen, changes may be overwritten and forever lost!
	Modify at your own risk!
	
	[ Generated on 2023.08.25 12:18:14 ]
*/

#include "Scripts.hpp"

namespace CppProject
{
	VarType render_generate_noise(RealType w, RealType h, VarType surf, RealType normal)
	{
		if (!surface_exists((IntType)(surf)))
			surf = surface_create((IntType)(w), (IntType)(h));
		surface_set_target((IntType)(surf));
	{
		draw_clear(c_white);
		for (IntType xx = IntType(0); xx <= w; xx++)
		{
			for (IntType yy = IntType(0); yy <= h; yy++)
			{
				RealType r, g, b, mag;
				r = random(1.0);
				g = random(1.0);
				b = random((normal > 0) ? 0.5 : 1.0);
				if (normal > 0)
				{
					mag = sqrt(r * r + g * g + b * b);
					r /= mag;
					g /= mag;
					b /= mag;
				}
				draw_point_color(xx, yy, make_color_rgb((IntType)(r * IntType(255)), (IntType)(g * IntType(255)), (IntType)(b * IntType(255))));
			}
		}
	}
		surface_reset_target();
		return surf;
	}
	
	ArrType render_generate_sample_kernel(RealType samples)
	{
		ArrType arr;
		for (RealType i = IntType(0); i < samples; i++)
		{
			RealType xx, yy, zz, mag, scale;
			xx = random_range(-1.0, 1.0);
			yy = random_range(-1.0, 1.0);
			zz = random_range(0.0, 1.0);
			mag = sqrt(xx * xx + yy * yy + zz * zz);
			xx /= mag;
			yy /= mag;
			zz /= mag;
			scale = i / samples;
			scale = lerp(0.1, 1.0, scale * scale);
			xx *= scale;
			yy *= scale;
			zz *= scale;
			if (abs(xx) < 0.01)
				xx = 0.01;
			if (abs(yy) < 0.01)
				yy = 0.01;
			if (abs(zz) < 0.01)
				zz = 0.01;
			arr[i * IntType(3)] = xx;
			arr[i * IntType(3) + IntType(1)] = yy;
			arr[i * IntType(3) + IntType(2)] = zz;
		}
		return arr;
	}
	
	VarType render_generate_text_buffer(VarType is3d, IntType surf, RealType xx, RealType zz, RealType wid, RealType hei)
	{
		vbuffer_start();
		if (is3d > 0)
			vbuffer_add_pixels({ surface_get_alpha_array(surf), point3D(xx, IntType(0), zz) });
		RealType ysize;
		VecType p1, p2, p3, p4, tsize, t1, t2, t3, t4;
		t1 = vec2(IntType(0), IntType(0));
		t2 = vec2(wid, IntType(0));
		t3 = vec2(wid, hei);
		t4 = vec2(IntType(0), hei);
		ysize = ((is3d > 0) ? IntType(1) : IntType(0));
		tsize = vec2(wid, hei);
		t1 = vec2_div(t1, tsize);
		t2 = vec2_div(t2, tsize);
		t3 = vec2_div(t3, tsize);
		t4 = vec2_div(t4, tsize);
		p1 = point3D(xx, ysize, zz + hei);
		p2 = point3D(xx + wid, ysize, zz + hei);
		p3 = point3D(xx + wid, ysize, zz);
		p4 = point3D(xx, ysize, zz);
		vbuffer_add_triangle({ p1, p2, p3, t1, t2, t3 });
		vbuffer_add_triangle({ p3, p4, p1, t3, t4, t1 });
		p1 = point3D(xx, IntType(0), zz + hei);
		p2 = point3D(xx + wid, IntType(0), zz + hei);
		p3 = point3D(xx + wid, IntType(0), zz);
		p4 = point3D(xx, IntType(0), zz);
		vbuffer_add_triangle({ p2, p1, p3, t2, t1, t3 });
		vbuffer_add_triangle({ p4, p3, p1, t4, t3, t1 });
		return vbuffer_done();
	}
	
	RealType render_generate_text(ScopeAny self, VarArgs argument)
	{
		IntType argument_count = argument.Size();
		VarType str, res, is3d, valign, halign, aa;
		BoolType alignmatch, aamatch;
		str = argument[IntType(0)];
		res = argument[IntType(1)];
		is3d = argument[IntType(2)];
		halign = /*"center"*/ STR(1420);
		valign = /*"center"*/ STR(1420);
		aa = true;
		alignmatch = true;
		aamatch = true;
		if (argument_count > IntType(3))
		{
			halign = argument[IntType(3)];
			valign = argument[IntType(4)];
			alignmatch = (sVar(text_halign_prev) == halign && sVar(text_valign_prev) == valign);
			if (!alignmatch)
			{
				sVar(text_halign_prev) = halign;
				sVar(text_valign_prev) = valign;
			}
		}
		if (argument_count > IntType(5))
		{
			aa = argument[IntType(5)];
			aamatch = (sVar(text_aa_prev) == aa);
			if (!aamatch)
				sVar(text_aa_prev) = aa;
		}
		if (sVar(text_texture).Value(IntType(0)) != null_ && sVar(text_string) == str && sVar(text_res) == res && sVar(text_3d) == is3d && alignmatch && aamatch)
			return IntType(0);
		if (string_char_at(str, string_length(str)) == /*"\n"*/ STR(943))
			str += /*" "*/ STR(21);
		sVar(text_string) = str;
		sVar(text_res) = res;
		sVar(text_3d) = is3d;
		draw_set_font((aa > 0) ? idInt(res, font) : idInt(res, font_no_aa));
		RealType wid, hei, xx, zz;
		wid = string_width(str) + IntType(3);
		hei = string_height_ext(str, (IntType)(string_height(/*" "*/ STR(21)) - IntType(2)), -IntType(1)) + IntType(1);
		switch (StringType(valign).id)
		{
			case 194: // top
			{
				zz = -hei;
				break;
			}
			case 1420: // center
			{
				zz = -hei / 2.0 - IntType(1);
				break;
			}
			case 193: // bottom
			{
				zz = IntType(0);
				break;
			}
		}
		
		switch (StringType(halign).id)
		{
			case 195: // left
			{
				xx = IntType(0);
				break;
			}
			case 1420: // center
			{
				xx = -wid / 2.0 - IntType(1);
				break;
			}
			case 196: // right
			{
				xx = -wid;
				break;
			}
		}
		
		IntType surf = surface_create((IntType)(wid), (IntType)(hei));
		surface_set_target(surf);
	{
		draw_clear_alpha(c_black, 0.0);
		IntType color = draw_get_color();
		draw_set_color(c_white);
		RealType textxx;
		switch (StringType(halign).id)
		{
			case 195: // left
			{
				textxx = IntType(0);
				draw_set_halign(fa_left);
				break;
			}
			case 1420: // center
			{
				textxx = ceil(wid / 2.0);
				draw_set_halign(fa_center);
				break;
			}
			case 196: // right
			{
				textxx = wid;
				draw_set_halign(fa_right);
				break;
			}
		}
		
		draw_text_ext((IntType)(textxx), -IntType(1), str, (IntType)(string_height(/*" "*/ STR(21)) - IntType(2)), -IntType(1));
		draw_set_halign(fa_left);
		draw_set_color(color);
	}
		surface_reset_target();
		IntType outlinesurf = surface_create((IntType)(wid), (IntType)(hei));
		surface_set_target(outlinesurf);
	{
		draw_clear_alpha(c_black, 0.0);
		gpu_set_texrepeat(false);
		global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_outline);
		withOne (Object, global::render_shader_obj, self->id)
		{
			shader_set(sInt(shader));
			shader_outline_set(wid, hei);
		}
		
		draw_surface_exists(surf, IntType(0), IntType(0));
		withOne (Object, global::render_shader_obj, self->id)
			shader_reset();
		
		gpu_set_texrepeat(true);
	}
		surface_reset_target();
		draw_set_font(global::_app->font_value);
		if (sVar(text_texture).Value(IntType(0)) != null_)
			texture_free(sVar(text_texture).Value(IntType(0)));
		sVar(text_texture)[IntType(0)] = texture_surface(surf);
		if (sVar(text_texture).Value(IntType(1)) != null_)
			texture_free(sVar(text_texture).Value(IntType(1)));
		sVar(text_texture)[IntType(1)] = texture_surface(outlinesurf);
		sVar(text_vbuffer)[IntType(0)] = render_generate_text_buffer(is3d, surf, xx, zz, wid, hei);
		sVar(text_vbuffer)[IntType(1)] = render_generate_text_buffer(is3d, outlinesurf, xx, zz, wid, hei);
		surface_free(surf);
		surface_free(outlinesurf);
		return true;
	}
	
	IntType render_get_noise_texture(RealType index)
	{
		if (array_length(VarType::CreateRef(global::render_sample_noise_texture_array)) < (index + IntType(1)) || !surface_exists(global::render_sample_noise_texture_array.Value(index)))
		{
			IntType surf, xoff, yoff;
			surf = surface_create(global::render_sample_noise_size, global::render_sample_noise_size);
			random_set_seed((IntType)(index));
			xoff = irandom_range(IntType(0), global::render_sample_noise_size);
			random_set_seed((IntType)(index + IntType(1000)));
			yoff = irandom_range(IntType(0), global::render_sample_noise_size);
			surface_set_target(surf);
		{
			draw_sprite(ID_spr_blue_noise, IntType(0), (IntType)(xoff - global::render_sample_noise_size), (IntType)(yoff - global::render_sample_noise_size));
			draw_sprite(ID_spr_blue_noise, IntType(0), (IntType)(xoff - global::render_sample_noise_size), yoff);
			draw_sprite(ID_spr_blue_noise, IntType(0), xoff, (IntType)(yoff - global::render_sample_noise_size));
			draw_sprite(ID_spr_blue_noise, IntType(0), xoff, yoff);
		}
			surface_reset_target();
			global::render_sample_noise_texture_array[index] = surf;
		}
		return global::render_sample_noise_texture_array.Value(index);
	}
	
	void render_high(ScopeAny self)
	{
		IntType starttime;
		RealType samplestart, sampleend;
		starttime = current_time();
		global::render_surface_time = IntType(0);
		render_update_samples();
		global::render_alpha_hash = sVar(project_render_alpha_mode);
		if (global::render_samples_done)
		{
			samplestart = IntType(0);
			sampleend = IntType(0);
		}
		else
		{
			samplestart = global::render_samples - IntType(1);
			sampleend = global::render_samples;
		}
		
		for (RealType s = samplestart; s < sampleend; s++)
		{
			global::render_sample_current = s;
			random_set_seed((IntType)(global::render_sample_current));
			render_high_update_taa();
			render_high_passes(self);
			if (global::render_shadows)
				render_high_shadows(self);
			if (global::render_indirect)
				render_high_indirect();
			if (global::render_ssao)
				render_high_ssao(self);
			VarType finalsurf;
			finalsurf = render_high_scene(self);
			if (global::render_reflections)
				render_high_reflections(finalsurf);
			finalsurf = render_high_tonemap(finalsurf);
			if (sVar(background_fog_show) > 0)
				render_high_fog(self, finalsurf);
			render_refresh_effects(true, false);
			finalsurf = render_post(self, finalsurf, true, false);
			global::render_target = surface_require(global::render_target, global::render_width, global::render_height);
			surface_set_target((IntType)(global::render_target));
		{
			if (global::render_pass > 0)
			{
				draw_clear_alpha(c_black, 1.0);
				draw_surface_exists(global::render_pass_surf, IntType(0), IntType(0));
			}
			else
			{
				draw_clear_alpha(c_black, 0.0);
				draw_surface_exists(finalsurf, IntType(0), IntType(0));
			}
			
		}
			surface_reset_target();
			render_high_samples_add();
		}
		render_high_samples_unpack();
		if (!(global::render_pass > 0))
		{
			VarType prevsurf;
			global::render_surface[IntType(0)] = surface_require(global::render_surface.Value(IntType(0)), global::render_width, global::render_height);
			prevsurf = global::render_surface.Value(IntType(0));
			gpu_set_blendmode_ext(bm_one, bm_zero);
			surface_set_target((IntType)(prevsurf));
		{
			draw_clear_alpha(c_black, 0.0);
			draw_surface_exists(global::render_target, IntType(0), IntType(0));
		}
			surface_reset_target();
			gpu_set_blendmode(bm_normal);
			render_refresh_effects(false, true);
			prevsurf = render_post(self, prevsurf, false, true);
			gpu_set_blendmode_ext(bm_one, bm_zero);
			surface_set_target((IntType)(global::render_target));
		{
			draw_clear_alpha(c_black, 0.0);
			draw_surface_exists(prevsurf, IntType(0), IntType(0));
		}
			surface_reset_target();
			gpu_set_blendmode(bm_normal);
		}
		global::taa_matrix = MAT_IDENTITY;
		global::render_samples_clear = false;
		global::render_alpha_hash = false;
		global::render_time = current_time() - starttime - global::render_surface_time;
	}
	
	VarType render_high_bloom(VarType prevsurf)
	{
		VarType thresholdsurf, bloomsurf, bloomsurftemp, resultsurf;
		RealType baseradius, bloomstrength;
		global::render_surface[IntType(0)] = surface_require(global::render_surface.Value(IntType(0)), global::render_width, global::render_height);
		global::render_surface[IntType(1)] = surface_require(global::render_surface.Value(IntType(1)), global::render_width, global::render_height);
		global::render_surface[IntType(2)] = surface_require(global::render_surface.Value(IntType(2)), global::render_width, global::render_height);
		thresholdsurf = global::render_surface.Value(IntType(0));
		bloomsurf = global::render_surface.Value(IntType(1));
		bloomsurftemp = global::render_surface.Value(IntType(2));
		resultsurf = render_high_get_apply_surf();
		baseradius = ((idVar(global::render_camera, value).Value(e_value_CAM_BLOOM_RADIUS) * IntType(10)) * (RealType)global::render_height / 500.0);
		bloomstrength = IntType(1);
		surface_set_target((IntType)(thresholdsurf));
	{
		draw_clear_alpha(c_black, 1.0);
		global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_high_bloom_threshold);
		withOne (Object, global::render_shader_obj, noone)
		{
			shader_set(sInt(shader));
			shader_high_bloom_threshold_set();
		}
		
		draw_surface_exists(prevsurf, IntType(0), IntType(0));
		withOne (Object, global::render_shader_obj, noone)
			shader_clear();
		
	}
		surface_reset_target();
		VarType blades;
		RealType bladerot, bladeangle;
		blades = max({ IntType(1), (RealType)idVar(global::render_camera, value).Value(e_value_CAM_BLADE_AMOUNT) / 2.0 });
		blades = frac(blades) > IntType(0) ? idVar(global::render_camera, value).Value(e_value_CAM_BLADE_AMOUNT) : blades;
		if (idVar(global::render_camera, value).Value(e_value_CAM_BLOOM_RATIO) > IntType(0) && blades > 0)
		{
			bladeangle = ((pi_ * IntType(2)) / (360.0 / idVar(global::render_camera, value).Value(e_value_CAM_BLADE_ANGLE)));
			for (IntType b = IntType(0); b < blades; b++)
			{
				bladerot = degtorad((180.0 / blades) * b) + bladeangle;
				surface_set_target((IntType)(bloomsurftemp));
			{
				draw_surface_exists(thresholdsurf, IntType(0), IntType(0));
			}
				surface_reset_target();
				for (IntType i = IntType(0); i < IntType(3); i++)
				{
					surface_set_target((IntType)(bloomsurf));
				{
					global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_blur);
					withOne (Object, global::render_shader_obj, noone)
					{
						shader_set(sInt(shader));
						shader_blur_set(global::render_blur_kernel, baseradius / (1.0 + 1.333 * i), cos(bladerot), sin(bladerot));
					}
					
					draw_surface_exists(bloomsurftemp, IntType(0), IntType(0));
					withOne (Object, global::render_shader_obj, noone)
						shader_clear();
					
				}
					surface_reset_target();
					surface_set_target((IntType)(bloomsurftemp));
				{
					draw_surface_exists(bloomsurf, IntType(0), IntType(0));
				}
					surface_reset_target();
				}
				bloomstrength = (1.0 / blades * idVar(global::render_camera, value).Value(e_value_CAM_BLOOM_RATIO) * idVar(global::render_camera, value).Value(e_value_CAM_BLOOM_INTENSITY));
				surface_set_target((IntType)(bloomsurftemp));
			{
				draw_clear_alpha(c_black, 0.0);
				draw_surface((IntType)(prevsurf), IntType(0), IntType(0));
			}
				surface_reset_target();
				surface_set_target((IntType)(prevsurf));
			{
				draw_clear_alpha(c_black, 0.0);
				global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_add);
				withOne (Object, global::render_shader_obj, noone)
				{
					shader_set(sInt(shader));
					shader_add_set(self, { bloomsurf, bloomstrength, idVar(global::render_camera, value).Value(e_value_CAM_BLOOM_BLEND) });
				}
				
				draw_surface_exists(bloomsurftemp, IntType(0), IntType(0));
				withOne (Object, global::render_shader_obj, noone)
					shader_clear();
				
			}
				surface_reset_target();
				if (global::render_camera_lens_dirt_bloom)
				{
					surface_set_target((IntType)(bloomsurftemp));
				{
					draw_clear_alpha(c_black, 0.0);
					draw_surface((IntType)(global::render_surface_lens), IntType(0), IntType(0));
				}
					surface_reset_target();
					surface_set_target((IntType)(global::render_surface_lens));
				{
					global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_add);
					withOne (Object, global::render_shader_obj, noone)
					{
						shader_set(sInt(shader));
						shader_add_set(self, { bloomsurf, bloomstrength, idVar(global::render_camera, value).Value(e_value_CAM_BLOOM_BLEND) });
					}
					
					draw_surface_exists(bloomsurftemp, IntType(0), IntType(0));
					withOne (Object, global::render_shader_obj, noone)
						shader_clear();
					
				}
					surface_reset_target();
				}
			}
		}
		if (idVar(global::render_camera, value).Value(e_value_CAM_BLOOM_RATIO) < IntType(1))
		{
			surface_set_target((IntType)(bloomsurftemp));
		{
			draw_surface_exists(thresholdsurf, IntType(0), IntType(0));
		}
			surface_reset_target();
			for (IntType i = IntType(0); i < IntType(3); i++)
			{
				surface_set_target((IntType)(bloomsurf));
			{
				global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_blur);
				withOne (Object, global::render_shader_obj, noone)
				{
					shader_set(sInt(shader));
					shader_blur_set(global::render_blur_kernel, baseradius / (1.0 + 1.333 * i), IntType(1), IntType(0));
				}
				
				draw_surface_exists(bloomsurftemp, IntType(0), IntType(0));
				withOne (Object, global::render_shader_obj, noone)
					shader_clear();
				
			}
				surface_reset_target();
				surface_set_target((IntType)(bloomsurftemp));
			{
				global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_blur);
				withOne (Object, global::render_shader_obj, noone)
				{
					shader_set(sInt(shader));
					shader_blur_set(global::render_blur_kernel, baseradius / (1.0 + 1.333 * i), IntType(0), IntType(1));
				}
				
				draw_surface_exists(bloomsurf, IntType(0), IntType(0));
				withOne (Object, global::render_shader_obj, noone)
					shader_clear();
				
			}
				surface_reset_target();
			}
			bloomstrength = ((1.0 - idVar(global::render_camera, value).Value(e_value_CAM_BLOOM_RATIO)) * idVar(global::render_camera, value).Value(e_value_CAM_BLOOM_INTENSITY));
			surface_set_target((IntType)(bloomsurftemp));
		{
			draw_clear_alpha(c_black, 0.0);
			draw_surface((IntType)(prevsurf), IntType(0), IntType(0));
		}
			surface_reset_target();
			surface_set_target((IntType)(prevsurf));
		{
			draw_clear_alpha(c_black, 0.0);
			global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_add);
			withOne (Object, global::render_shader_obj, noone)
			{
				shader_set(sInt(shader));
				shader_add_set(self, { bloomsurf, bloomstrength, idVar(global::render_camera, value).Value(e_value_CAM_BLOOM_BLEND) });
			}
			
			draw_surface_exists(bloomsurftemp, IntType(0), IntType(0));
			withOne (Object, global::render_shader_obj, noone)
				shader_clear();
			
		}
			surface_reset_target();
			if (global::render_camera_lens_dirt_bloom)
			{
				surface_set_target((IntType)(bloomsurftemp));
			{
				draw_clear_alpha(c_black, 0.0);
				draw_surface((IntType)(global::render_surface_lens), IntType(0), IntType(0));
			}
				surface_reset_target();
				surface_set_target((IntType)(global::render_surface_lens));
			{
				global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_add);
				withOne (Object, global::render_shader_obj, noone)
				{
					shader_set(sInt(shader));
					shader_add_set(self, { bloomsurf, bloomstrength, idVar(global::render_camera, value).Value(e_value_CAM_BLOOM_BLEND) });
				}
				
				draw_surface_exists(bloomsurftemp, IntType(0), IntType(0));
				withOne (Object, global::render_shader_obj, noone)
					shader_clear();
				
			}
				surface_reset_target();
			}
		}
		surface_set_target((IntType)(resultsurf));
	{
		draw_clear_alpha(c_black, 0.0);
		draw_surface((IntType)(prevsurf), IntType(0), IntType(0));
	}
		surface_reset_target();
		return resultsurf;
	}
	
	VarType render_high_ca(VarType prevsurf)
	{
		VarType resultsurf = render_high_get_apply_surf();
		gpu_set_texrepeat(false);
		surface_set_target((IntType)(resultsurf));
	{
		draw_clear_alpha(c_black, 0.0);
		global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_ca);
		withOne (Object, global::render_shader_obj, noone)
			shader_use(self);
		
		draw_surface_exists(prevsurf, IntType(0), IntType(0));
		withOne (Object, global::render_shader_obj, noone)
			shader_clear();
		
	}
		surface_reset_target();
		gpu_set_texrepeat(true);
		return resultsurf;
	}
	
	VarType render_high_cc(VarType prevsurf)
	{
		VarType resultsurf = render_high_get_apply_surf();
		surface_set_target((IntType)(resultsurf));
	{
		draw_clear_alpha(c_black, 0.0);
		global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_color_correction);
		withOne (Object, global::render_shader_obj, noone)
			shader_use(self);
		
		draw_surface_exists(prevsurf, IntType(0), IntType(0));
		withOne (Object, global::render_shader_obj, noone)
			shader_clear();
		
	}
		surface_reset_target();
		return resultsurf;
	}
	
	VarType render_high_distort(VarType prevsurf)
	{
		VarType resultsurf = render_high_get_apply_surf();
		gpu_set_texfilter(true);
		surface_set_target((IntType)(resultsurf));
	{
		draw_clear_alpha(c_black, 0.0);
		global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_distort);
		withOne (Object, global::render_shader_obj, noone)
			shader_use(self);
		
		draw_surface_exists(prevsurf, IntType(0), IntType(0));
		withOne (Object, global::render_shader_obj, noone)
			shader_clear();
		
	}
		surface_reset_target();
		gpu_set_texfilter(false);
		return resultsurf;
	}
	
	VarType render_high_dof(ScopeAny self, VarType prevsurf)
	{
		VarType depthsurf, cocsurf, resultsurf;
		global::render_surface[IntType(0)] = surface_require(global::render_surface.Value(IntType(0)), global::render_width, global::render_height);
		depthsurf = global::render_surface.Value(IntType(0));
		surface_set_target((IntType)(depthsurf));
	{
		gpu_set_blendmode_ext(bm_one, bm_zero);
		draw_clear(c_white);
		render_world_start();
		render_world(self, e_render_mode_DEPTH);
		render_world_done();
		gpu_set_blendmode(bm_normal);
	}
		surface_reset_target();
		global::render_surface[IntType(1)] = surface_require(global::render_surface.Value(IntType(1)), global::render_width, global::render_height);
		cocsurf = global::render_surface.Value(IntType(1));
		surface_set_target((IntType)(cocsurf));
	{
		draw_clear(c_black);
		global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_high_dof_coc);
		withOne (Object, global::render_shader_obj, global::_app->id)
		{
			shader_set(sInt(shader));
			shader_high_dof_coc_set(self, depthsurf);
		}
		
		draw_blank(IntType(0), IntType(0), global::render_width, global::render_height);
		draw_surface_exists(prevsurf, IntType(0), IntType(0));
		withOne (Object, global::render_shader_obj, global::_app->id)
			shader_clear();
		
	}
		surface_reset_target();
		gpu_set_texrepeat(false);
		for (IntType _it = 0, _it_max = IntType(16); _it < _it_max; _it++)
		{
			VarType cocsurftemp;
			global::render_surface[IntType(2)] = surface_require(global::render_surface.Value(IntType(2)), global::render_width, global::render_height);
			cocsurftemp = global::render_surface.Value(IntType(2));
			global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_high_dof_coc_blur);
			withOne (Object, global::render_shader_obj, global::_app->id)
				shader_set(sInt(shader));
			
			surface_set_target((IntType)(cocsurftemp));
		{
			withOne (Object, global::render_shader_obj, global::_app->id)
				shader_high_dof_coc_blur_set(IntType(1), IntType(0));
			
			draw_surface_exists(cocsurf, IntType(0), IntType(0));
		}
			surface_reset_target();
			surface_set_target((IntType)(cocsurf));
		{
			withOne (Object, global::render_shader_obj, global::_app->id)
				shader_high_dof_coc_blur_set(IntType(0), IntType(1));
			
			draw_surface_exists(cocsurftemp, IntType(0), IntType(0));
		}
			surface_reset_target();
			withOne (Object, global::render_shader_obj, global::_app->id)
				shader_clear();
			
		}
		gpu_set_texrepeat(true);
		resultsurf = render_high_get_apply_surf();
		surface_set_target((IntType)(resultsurf));
	{
		draw_clear_alpha(c_black, 0.0);
		gpu_set_texfilter(true);
		gpu_set_texrepeat(false);
		global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_high_dof);
		withOne (Object, global::render_shader_obj, global::_app->id)
		{
			shader_set(sInt(shader));
			shader_high_dof_set(self, cocsurf);
		}
		
		draw_surface_exists(prevsurf, IntType(0), IntType(0));
		withOne (Object, global::render_shader_obj, global::_app->id)
			shader_clear();
		
		gpu_set_texfilter(false);
		gpu_set_texrepeat(true);
	}
		surface_reset_target();
		return resultsurf;
	}
	
	void render_high_fog(ScopeAny self, VarType basesurf)
	{
		VarType fogsurf, prevsurf;
		global::render_surface[IntType(1)] = surface_require(global::render_surface.Value(IntType(1)), global::render_width, global::render_height);
		global::render_surface[IntType(2)] = surface_require(global::render_surface.Value(IntType(2)), global::render_width, global::render_height);
		fogsurf = global::render_surface.Value(IntType(1));
		prevsurf = global::render_surface.Value(IntType(2));
		surface_set_target((IntType)(fogsurf));
	{
		draw_clear(c_black);
		render_world_start();
		render_world(self, e_render_mode_HIGH_FOG);
		render_world_done();
	}
		surface_reset_target();
		surface_set_target((IntType)(prevsurf));
	{
		draw_clear_alpha(c_black, 0.0);
		draw_surface_exists(basesurf, IntType(0), IntType(0));
	}
		surface_reset_target();
		surface_set_target((IntType)(basesurf));
	{
		draw_clear_alpha(c_black, 0.0);
		draw_surface_exists(prevsurf, IntType(0), IntType(0));
		if (sVar(background_fog_show) > 0)
		{
			global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_high_fog_apply);
			withOne (Object, global::render_shader_obj, global::_app->id)
			{
				shader_set(sInt(shader));
				shader_high_fog_apply_set(self, fogsurf);
			}
			
			draw_blank(IntType(0), IntType(0), global::render_width, global::render_height);
			withOne (Object, global::render_shader_obj, global::_app->id)
				shader_clear();
			
		}
		gpu_set_blendmode_ext(bm_src_color, bm_one);
		if (global::render_background > 0)
			draw_box(IntType(0), IntType(0), global::render_width, global::render_height, false, c_black, IntType(1));
		else
		{
			render_world_start();
			render_world(self, e_render_mode_ALPHA_FIX);
			render_world_done();
		}
		
		gpu_set_blendmode(bm_normal);
	}
		surface_reset_target();
	}
	
	VarType render_high_get_apply_surf()
	{
		global::render_post_index = !(global::render_post_index > 0);
		if (global::render_post_index > 0)
		{
			global::render_surface_material = surface_require(global::render_surface_material, global::render_width, global::render_height);
			return global::render_surface_material;
		}
		else
		{
			global::render_surface_diffuse = surface_require(global::render_surface_diffuse, global::render_width, global::render_height);
			return global::render_surface_diffuse;
		}
		
		return VarType();
	}
	
	VarType render_high_glow(ScopeAny self, VarType prevsurf, RealType glowfalloff)
	{
		VarType glowcolorsurf, glowsurf, resultsurf;
		global::render_surface[IntType(0)] = surface_require(global::render_surface.Value(IntType(0)), global::render_width, global::render_height);
		global::render_surface[IntType(1)] = surface_require(global::render_surface.Value(IntType(1)), global::render_width, global::render_height);
		glowcolorsurf = global::render_surface.Value(IntType(0));
		glowsurf = global::render_surface.Value(IntType(1));
		surface_set_target((IntType)(glowcolorsurf));
	{
		draw_clear_alpha(c_black, 1.0);
		render_world_start();
		render_world(self, e_render_mode_COLOR_GLOW);
		render_world_done();
		render_set_projection_ortho(IntType(0), IntType(0), global::render_width, global::render_height, IntType(0));
		gpu_set_blendmode_ext(bm_src_color, bm_one);
		draw_box(IntType(0), IntType(0), global::render_width, global::render_height, false, c_black, IntType(1));
		gpu_set_blendmode(bm_normal);
	}
		surface_reset_target();
		VarType glowsurftemp;
		global::render_surface[IntType(2)] = surface_require(global::render_surface.Value(IntType(2)), global::render_width, global::render_height);
		glowsurftemp = global::render_surface.Value(IntType(2));
		global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_blur);
		withOne (Object, global::render_shader_obj, global::_app->id)
			shader_set(sInt(shader));
		
		RealType baseradius;
		if (glowfalloff > 0)
			baseradius = ((sVar(project_render_glow_radius) * sVar(project_render_glow_falloff_radius) * IntType(10)) * (RealType)global::render_height / 500.0);
		else
			baseradius = ((sVar(project_render_glow_radius) * IntType(10)) * (RealType)global::render_height / 500.0);
		
		gpu_set_tex_repeat(false);
		gpu_set_texfilter(true);
		for (IntType i = IntType(0); i < IntType(3); i++)
		{
			RealType radius = baseradius / (1.0 + 1.333 * i);
			surface_set_target((IntType)(glowsurftemp));
		{
			withOne (Object, global::render_shader_obj, global::_app->id)
				shader_blur_set(global::render_blur_kernel, radius, IntType(1), IntType(0));
			
			if (i == IntType(0))
				draw_surface_exists(glowcolorsurf, IntType(0), IntType(0));
			else
				draw_surface_exists(glowsurf, IntType(0), IntType(0));
			
		}
			surface_reset_target();
			surface_set_target((IntType)(glowsurf));
		{
			withOne (Object, global::render_shader_obj, global::_app->id)
				shader_blur_set(global::render_blur_kernel, radius, IntType(0), IntType(1));
			
			draw_surface_exists(glowsurftemp, IntType(0), IntType(0));
		}
			surface_reset_target();
		}
		withOne (Object, global::render_shader_obj, global::_app->id)
			shader_clear();
		
		gpu_set_tex_repeat(true);
		gpu_set_texfilter(false);
		resultsurf = render_high_get_apply_surf();
		surface_set_target((IntType)(resultsurf));
	{
		draw_clear_alpha(c_black, 0.0);
		global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_add);
		withOne (Object, global::render_shader_obj, global::_app->id)
		{
			shader_set(sInt(shader));
			shader_add_set(self, { glowsurf, (glowfalloff > 0) ? global::_app->project_render_glow_falloff_intensity : global::_app->project_render_glow_intensity, c_white });
		}
		
		draw_surface_exists(prevsurf, IntType(0), IntType(0));
		withOne (Object, global::render_shader_obj, global::_app->id)
			shader_clear();
		
	}
		surface_reset_target();
		if (global::render_camera_lens_dirt_glow)
		{
			global::render_surface[IntType(0)] = surface_require(global::render_surface.Value(IntType(0)), global::render_width, global::render_height);
			prevsurf = global::render_surface.Value(IntType(0));
			surface_set_target((IntType)(prevsurf));
		{
			draw_clear_alpha(c_black, 1.0);
			draw_surface((IntType)(global::render_surface_lens), IntType(0), IntType(0));
		}
			surface_reset_target();
			surface_set_target((IntType)(global::render_surface_lens));
		{
			draw_clear_alpha(c_black, 1.0);
			global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_add);
			withOne (Object, global::render_shader_obj, global::_app->id)
			{
				shader_set(sInt(shader));
				shader_add_set(self, { glowsurf, global::_app->project_render_glow_intensity, c_white });
			}
			
			draw_surface_exists(prevsurf, IntType(0), IntType(0));
			withOne (Object, global::render_shader_obj, global::_app->id)
				shader_clear();
			
		}
			surface_reset_target();
		}
		return resultsurf;
	}
	
	VarType render_high_grain(VarType prevsurf)
	{
		VarType resultsurf = render_high_get_apply_surf();
		RealType size = max({ ceil((RealType)global::render_width / 8.0), ceil((RealType)global::render_height / 8.0) });
		global::render_grain_noise = surface_require(global::render_grain_noise, size, size);
		random_set_seed((IntType)(global::_app->background_time));
		render_generate_noise(size, size, global::render_grain_noise);
		surface_set_target((IntType)(resultsurf));
	{
		draw_clear_alpha(c_black, 0.0);
		global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_noise);
		withOne (Object, global::render_shader_obj, global::_app->id)
			shader_use(self);
		
		draw_surface_exists(prevsurf, IntType(0), IntType(0));
		withOne (Object, global::render_shader_obj, global::_app->id)
			shader_clear();
		
	}
		surface_reset_target();
		return resultsurf;
	}
	
	void render_high_indirect()
	{
		global::render_surface_hdr[IntType(0)] = surface_require(global::render_surface_hdr.Value(IntType(0)), global::render_width, global::render_height, true, true);
		surface_set_target((IntType)(global::render_surface_hdr.Value(IntType(0))));
	{
		gpu_set_texrepeat(false);
		draw_clear_alpha(c_black, 1.0);
		global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_high_raytrace);
		withOne (Object, global::render_shader_obj, noone)
		{
			shader_set(sInt(shader));
			shader_high_raytrace_set(self, e_raytrace_INDIRECT);
		}
		
		draw_blank(IntType(0), IntType(0), global::render_width, global::render_height);
		withOne (Object, global::render_shader_obj, noone)
			shader_clear();
		
		gpu_set_texrepeat(true);
	}
		surface_reset_target();
		global::render_surface_hdr[IntType(1)] = surface_require(global::render_surface_hdr.Value(IntType(1)), global::render_width, global::render_height, true, true);
		surface_set_target((IntType)(global::render_surface_hdr.Value(IntType(1))));
	{
		draw_clear_alpha(c_black, 0.0);
		global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_high_raytrace_resolve);
		withOne (Object, global::render_shader_obj, noone)
		{
			shader_set(sInt(shader));
			shader_high_raytrace_resolve_set(self, true);
		}
		
		draw_surface_exists(global::render_surface_hdr.Value(IntType(0)), IntType(0), IntType(0));
		withOne (Object, global::render_shader_obj, noone)
			shader_clear();
		
	}
		surface_reset_target();
		if (global::_app->project_render_indirect_blur_radius > IntType(0))
		{
			surface_set_target((IntType)(global::render_surface_hdr.Value(IntType(0))));
		{
			draw_clear_alpha(c_black, 0.0);
			global::render_shader_obj = DsMap(global::shader_map).Value(ID_shader_high_indirect_blur);
			withOne (Object, global::render_shader_obj, noone)
			{
				shader_set(sInt(shader));
				shader_high_indirect_blur_set(self);
			}
			
			draw_surface_exists(global::render_surface_hdr.Value(IntType(1)), IntType(0), IntType(0));
			withOne (Object, global::render_shader_obj, noone)
				shader_clear();
			
		}
			surface_reset_target();
		}
		VarType indirectsurf = (global::_app->project_render_indirect_blur_radius > IntType(0) ? global::render_surface_hdr.Value(IntType(0)) : global::render_surface_hdr.Value(IntType(1)));
		surface_set_target((IntType)(global::render_surface_shadows));
	{
		gpu_set_blendmode(bm_add);
		draw_surface_exists(indirectsurf, IntType(0), IntType(0));
		gpu_set_blendmode(bm_normal);
	}
		surface_reset_target();
		if (global::render_pass == e_render_pass_INDIRECT)
			global::render_pass_surf = surface_duplicate(indirectsurf);
		if (global::render_pass == e_render_pass_INDIRECT_SHADOWS)
			global::render_pass_surf = surface_duplicate(global::render_surface_shadows);
	}
	
}
