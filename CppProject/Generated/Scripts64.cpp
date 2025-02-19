/*
	NOTE:
	This file was autogenerated by CppGen, changes may be overwritten and forever lost!
	Modify at your own risk!
	
	[ Generated on 2023.10.28 18:38:26 ]
*/

#include "Scripts.hpp"

namespace CppProject
{
	VarType temp_get_shape_tex(VarType texobj, VarType def)
	{
		if (texobj != null_)
		{
			if (idVar(texobj, type) == e_tl_type_CAMERA)
			{
				global::shader_texture_surface = true;
				return idVar(texobj, cam_surf);
			}
			else
				return idVar(texobj, texture);
			
		}
		if (def != VarType())
			return def;
		else
			return global::shape_texture;
		
		return VarType();
	}
	
	VarType temp_get_shape_texobj(ScopeAny self, VarType val)
	{
		if (val == IntType(0))
			return null_;
		if (val == null_)
			return sVar(shape_tex);
		if (idVar(val, type) == e_tl_type_CAMERA)
		{
			if (surface_exists((IntType)(idVar(val, cam_surf))))
				return val;
		}
		else
			if (idVar(val, texture) != null_)
				return val;
		
		return null_;
	}
	
	VarType temp_get_shape_tex_material_obj(ScopeAny self, VarType val)
	{
		if (val == IntType(0))
			return null_;
		if (val == null_)
			return sVar(shape_tex_material);
		if (idVar(val, texture) != null_)
			return val;
		return null_;
	}
	
	VarType temp_get_shape_tex_normal_obj(ScopeAny self, VarType val)
	{
		if (val == IntType(0))
			return null_;
		if (val == null_)
			return sVar(shape_tex_normal);
		if (idVar(val, texture) != null_)
			return val;
		return null_;
	}
	
	void temp_particles_copy(ScopeAny self, VarType to)
	{
		idVar(to, pc_spawn_constant) = sVar(pc_spawn_constant);
		idVar(to, pc_spawn_amount) = sVar(pc_spawn_amount);
		idVar(to, pc_spawn_region_use) = sVar(pc_spawn_region_use);
		idVar(to, pc_spawn_region_type) = sVar(pc_spawn_region_type);
		idVar(to, pc_spawn_region_path) = sVar(pc_spawn_region_path);
		idVar(to, pc_spawn_region_sphere_radius) = sVar(pc_spawn_region_sphere_radius);
		idVar(to, pc_spawn_region_cube_size) = sVar(pc_spawn_region_cube_size);
		idVar(to, pc_spawn_region_box_size) = sVar(pc_spawn_region_box_size);
		idVar(to, pc_spawn_region_path_radius) = sVar(pc_spawn_region_path_radius);
		idVar(to, pc_bounding_box_type) = sVar(pc_bounding_box_type);
		idVar(to, pc_bounding_box_ground_z) = sVar(pc_bounding_box_ground_z);
		idVar(to, pc_bounding_box_custom_start) = sVar(pc_bounding_box_custom_start);
		idVar(to, pc_bounding_box_custom_end) = sVar(pc_bounding_box_custom_end);
		idVar(to, pc_bounding_box_relative) = sVar(pc_bounding_box_relative);
		idVar(to, pc_destroy_at_animation_finish) = sVar(pc_destroy_at_animation_finish);
		idVar(to, pc_destroy_at_amount) = sVar(pc_destroy_at_amount);
		idVar(to, pc_destroy_at_amount_val) = sVar(pc_destroy_at_amount_val);
		idVar(to, pc_destroy_at_time) = sVar(pc_destroy_at_time);
		idVar(to, pc_destroy_at_time_seconds) = sVar(pc_destroy_at_time_seconds);
		idVar(to, pc_destroy_at_time_israndom) = sVar(pc_destroy_at_time_israndom);
		idVar(to, pc_destroy_at_time_random_min) = sVar(pc_destroy_at_time_random_min);
		idVar(to, pc_destroy_at_time_random_max) = sVar(pc_destroy_at_time_random_max);
		idVar(to, pc_destroy_at_bounding_box) = sVar(pc_destroy_at_bounding_box);
	}
	
	void temp_particles_init(ScopeAny self)
	{
		sVar(pc_spawn_constant) = true;
		sVar(pc_spawn_amount) = IntType(100);
		sVar(pc_spawn_region_use) = IntType(0);
		sVar(pc_spawn_region_type) = /*"sphere"*/ STR(526);
		sVar(pc_spawn_region_path) = null_;
		sVar(pc_spawn_region_sphere_radius) = IntType(100);
		sVar(pc_spawn_region_cube_size) = IntType(200);
		sVar(pc_spawn_region_box_size) = vec3(IntType(200), IntType(200), IntType(200));
		sVar(pc_spawn_region_path_radius) = IntType(8);
		sVar(pc_bounding_box_type) = /*"none"*/ STR(878);
		sVar(pc_bounding_box_ground_z) = IntType(0);
		sVar(pc_bounding_box_custom_start) = vec3(-IntType(100), -IntType(100), -IntType(100));
		sVar(pc_bounding_box_custom_end) = vec3(IntType(100), IntType(100), IntType(100));
		sVar(pc_bounding_box_relative) = IntType(0);
		sVar(pc_destroy_at_animation_finish) = true;
		sVar(pc_destroy_at_amount) = true;
		sVar(pc_destroy_at_amount_val) = IntType(200);
		sVar(pc_destroy_at_time) = IntType(0);
		sVar(pc_destroy_at_time_seconds) = IntType(5);
		sVar(pc_destroy_at_time_israndom) = IntType(0);
		sVar(pc_destroy_at_time_random_min) = IntType(5);
		sVar(pc_destroy_at_time_random_max) = IntType(10);
		sVar(pc_destroy_at_bounding_box) = false;
		sInt(pc_type_list) = ds_list_create();
	}
	
	void temp_particles_restart(ScopeAny self)
	{
		withAll (obj_timeline, self->id)
			if (self->temp == self.otherId)
				particle_spawner_clear(ScopeAny(self));
		
		withAll (obj_preview, self->id)
			if (self->select == self.otherId)
				particle_spawner_clear(ScopeAny(self));
		
	}
	
	IntType temp_particles_type_add(ScopeAny self)
	{
		IntType ptype = (new obj_particle_type)->id;
		ObjType(obj_particle_type, ptype)->creator = self->id;
		ds_list_add({ sInt(pc_type_list), ptype });
		ObjType(obj_particle_type, ptype)->name = text_get({ /*"particleeditortypedefault"*/ STR(3796), string(ds_list_size(sInt(pc_type_list))) });
		ObjType(obj_particle_type, ptype)->spawn_rate = 1.0 / ds_list_size(sInt(pc_type_list));
		ObjType(obj_particle_type, ptype)->sprite_tex = global::mc_res;
		idInt(ObjType(obj_particle_type, ptype)->sprite_tex, count)++;
		ObjType(obj_particle_type, ptype)->sprite_template_tex = global::mc_res;
		idInt(ObjType(obj_particle_type, ptype)->sprite_template_tex, count)++;
		withOne (obj_particle_type, ptype, self->id)
			ptype_update_sprite_vbuffers(ScopeAny(self));
		
		temp_particles_update_spawn_rate(self, ptype, ObjType(obj_particle_type, ptype)->spawn_rate);
		temp_particles_restart(self);
		return ptype;
	}
	
	void temp_particles_type_clear(ScopeAny self)
	{
		while (ds_list_size(sInt(pc_type_list)))
			withOne (obj_particle_type, DsList(sInt(pc_type_list)).Value(IntType(0)), self->id)
				instance_destroy(ScopeAny(self));
		
		
	}
	
	IntType temp_particles_type_duplicate(ScopeAny self, VarType type)
	{
		IntType ptype = (new obj_particle_type)->id;
		withOne (Object, type, self->id)
			ptype_copy(self, ptype);
		
		ds_list_add({ sInt(pc_type_list), ptype });
		ObjType(obj_particle_type, ptype)->spawn_rate = 1.0 / ds_list_size(sInt(pc_type_list));
		idInt(ObjType(obj_particle_type, ptype)->sprite_tex, count)++;
		withOne (obj_particle_type, ptype, self->id)
			ptype_update_sprite_vbuffers(ScopeAny(self));
		
		temp_particles_update_spawn_rate(self, ptype, ObjType(obj_particle_type, ptype)->spawn_rate);
		temp_particles_restart(self);
		return ptype;
	}
	
	void temp_particles_type_remove(ScopeAny self, VarType ptype)
	{
		for (IntType t = IntType(0); t < ds_list_size(sInt(pc_type_list)); t++)
			if (DsList(sInt(pc_type_list)).Value(t) != ptype)
				ObjType(obj_particle_type, DsList(sInt(pc_type_list))[t])->spawn_rate += (RealType)idVar(ptype, spawn_rate) / (ds_list_size(sInt(pc_type_list)) - IntType(1));
		withOne (Object, ptype, self->id)
			instance_destroy(self);
		
		temp_particles_restart(self);
	}
	
	void temp_particles_update_spawn_rate(ScopeAny self, VarType ptype, VarType val)
	{
		VarType sub = val;
		for (IntType t = IntType(0); t < ds_list_size(sInt(pc_type_list)); t++)
		{
			IntType curptype = DsList(sInt(pc_type_list)).Value(t);
			if (curptype == ptype)
				continue;
			ObjType(obj_particle_type, curptype)->spawn_rate -= (RealType)val / (ds_list_size(sInt(pc_type_list)) - IntType(1));
			sub -= (RealType)val / (ds_list_size(sInt(pc_type_list)) - IntType(1));
			if (ObjType(obj_particle_type, curptype)->spawn_rate < IntType(0))
				sub += abs(ObjType(obj_particle_type, curptype)->spawn_rate);
			ObjType(obj_particle_type, curptype)->spawn_rate = max({ IntType(0), ObjType(obj_particle_type, curptype)->spawn_rate });
		}
		if (sub > IntType(0))
		{
			for (IntType t = IntType(0); t < ds_list_size(sInt(pc_type_list)); t++)
			{
				IntType curptype = DsList(sInt(pc_type_list)).Value(t);
				if (curptype == ptype || ObjType(obj_particle_type, curptype)->spawn_rate == IntType(0))
					continue;
				ObjType(obj_particle_type, curptype)->spawn_rate -= sub;
				if (ObjType(obj_particle_type, curptype)->spawn_rate < IntType(0))
					sub += abs(ObjType(obj_particle_type, curptype)->spawn_rate);
				else
					break;
				
				ObjType(obj_particle_type, curptype)->spawn_rate = max({ IntType(0), ObjType(obj_particle_type, curptype)->spawn_rate });
			}
		}
	}
	
	void temp_set_scenery(ScopeAny self, VarType res, BoolType animate, IntType hobj)
	{
		if (sVar(scenery) != null_)
			idInt(sVar(scenery), count)--;
		withAll (obj_timeline, self->id)
		{
			if (self->temp != self.otherId || self->part_list == null_)
				continue;
			IntType root = self->id;
			for (IntType p = IntType(0); p < ds_list_size(self->part_list); p++)
			{
				withOne (Object, DsList(self->part_list).Value(p), self->id)
				{
					if (hobj != null_)
					{
						for (IntType t = IntType(0); t < ds_list_size(sInt(tree_list)); t++)
						{
							withOne (Object, DsList(sInt(tree_list)).Value(t), self->id)
							{
								if (sVar(part_of) != null_)
									continue;
								withOne (obj_history, hobj, self->id)
								{
									self->part_child_save_id[self->part_child_amount] = idVar(self.otherId, save_id);
									self->part_child_parent_save_id[self->part_child_amount] = idVar(idVar(self.otherId, parent), save_id);
									self->part_child_parent_tree_index[self->part_child_amount] = t;
									self->part_child_amount++;
								}
								
							}
							
						}
					}
					for (IntType t = IntType(0); t < ds_list_size(sInt(tree_list)); t++)
					{
						withOne (Object, DsList(sInt(tree_list)).Value(t), self->id)
						{
							if (sVar(part_of) == null_)
							{
								tl_set_parent(self, { root });
								t--;
							}
						}
						
					}
					if (sInt(part_list) != null_)
					{
						for (IntType sp = IntType(0); sp < ds_list_size(sInt(part_list)); sp++)
						{
							withOne (Object, DsList(sInt(part_list)).Value(sp), self->id)
							{
								if (hobj != null_)
								{
									for (IntType t = IntType(0); t < ds_list_size(sInt(tree_list)); t++)
									{
										withOne (Object, DsList(sInt(tree_list)).Value(t), self->id)
										{
											if (sVar(part_of) != null_)
												continue;
											withOne (obj_history, hobj, self->id)
											{
												self->part_child_save_id[self->part_child_amount] = idVar(self.otherId, save_id);
												self->part_child_parent_save_id[self->part_child_amount] = idVar(idVar(self.otherId, parent), save_id);
												self->part_child_parent_tree_index[self->part_child_amount] = t;
												self->part_child_amount++;
											}
											
										}
										
									}
								}
								for (IntType t = IntType(0); t < ds_list_size(sInt(tree_list)); t++)
								{
									withOne (Object, DsList(sInt(tree_list)).Value(t), self->id)
									{
										if (sVar(part_of) == null_)
										{
											tl_set_parent(self, { root });
											t--;
										}
									}
									
								}
							}
							
						}
					}
					withOne (obj_history, hobj, self->id)
						self->part_save_obj[self->part_amount++] = history_save_tl(ScopeAny(self), self.otherId);
					
				}
				
			}
			while (ds_list_size(self->part_list) > IntType(0))
				tl_remove_clean(ScopeAny(self), { DsList(self->part_list).Value(IntType(0)) });
			
			withAll (obj_timeline, self->id)
				if (self->delete_ready)
					instance_destroy(ScopeAny(self));
			
			ds_list_clear(self->part_list);
		}
		
		sVar(scenery) = res;
		if (sVar(scenery) != null_)
		{
			idInt(sVar(scenery), count)++;
			if (animate)
			{
				withAll (obj_timeline, self->id)
				{
					if (self->temp != self.otherId)
						continue;
					if (idBool(idVar(self->temp, scenery), ready))
						tl_animate_scenery(self);
					else
						self->scenery_animate = true;
					
				}
				
			}
			if (idBool(sVar(scenery), ready))
			{
				temp_update_display_name(self);
				temp_update_rot_point(self);
				withOne (app, global::_app->id, self->id)
					tl_update_matrix(ScopeAny(self));
				
			}
		}
	}
	
	void temp_update(ScopeAny self, BoolType copy)
	{
		if (sVar(type) == e_temp_type_CHARACTER || sVar(type) == e_temp_type_SPECIAL_BLOCK || sVar(type) == e_temp_type_BODYPART || sVar(type) == e_temp_type_MODEL)
		{
			temp_update_model(self, copy);
			if (sVar(type) == e_temp_type_BODYPART)
				temp_update_model_part(self);
			temp_update_model_shape(self);
		}
		else
			if (sVar(type) == e_temp_type_ITEM)
				render_generate_item(self);
			else
				if (sVar(type) == e_temp_type_BLOCK)
					temp_update_block(self);
				else
					if (type_is_shape(sVar(type)))
						temp_update_shape(self);
			
		
		
		if (self->subAssetId != ID_obj_bench_settings)
		{
			temp_update_rot_point(self);
			temp_update_display_name(self);
			withOne (app, global::_app->id, self->id)
			{
				tl_update_list(ScopeAny(self));
				tl_update_matrix(ScopeAny(self));
			}
			
		}
	}
	
	RealType temp_update_armor(VarType temp)
	{
		if (idVar(temp, model_name) != /*"armor"*/ STR(751))
			return IntType(0);
		VarType state, type;
		state = /*""*/ STR(0);
		type = /*""*/ STR(0);
		for (IntType i = IntType(0); i < array_length(VarType::CreateRef(idVar(temp, model_state))); i += IntType(2))
		{
			state = idVar(temp, model_state).Value(i);
			type = idVar(temp, model_state).Value(i + IntType(1));
			if (state == /*"helmet"*/ STR(1995))
				idArr(temp, armor_array)[IntType(0)] = type;
			else
				if (state == /*"chestplate"*/ STR(1996))
					idArr(temp, armor_array)[IntType(4)] = type;
				else
					if (state == /*"leggings"*/ STR(1997))
						idArr(temp, armor_array)[IntType(8)] = type;
					else
						if (state == /*"boots"*/ STR(1998))
							idArr(temp, armor_array)[IntType(12)] = type;
				
			
			
		}
		array_add(VarType::CreateRef(global::armor_update), temp);
		return 0.0;
	}
	
	void temp_update_block(ScopeAny self)
	{
		block_vbuffer_start(self);
		withOne (obj_builder, global::mc_builder, self->id)
		{
			self->build_single_block = DsMap(ObjType(obj_minecraft_assets, global::mc_assets)->block_name_map).Value(idVar(self.otherId, block_name));
			self->build_single_stateid = block_get_state_id(self->build_single_block, idArr(self.otherId, block_state));
			if (idVar(self.otherId, block_repeat_enable) > 0)
			{
				self->build_size_x = idVar(self.otherId, block_repeat).Value(Y_);
				self->build_size_y = idVar(self.otherId, block_repeat).Value(X_);
				self->build_size_z = idVar(self.otherId, block_repeat).Value(Z_);
			}
			else
			{
				self->build_size_x = IntType(1);
				self->build_size_y = IntType(1);
				self->build_size_z = IntType(1);
			}
			
			self->build_randomize = idVar(self.otherId, block_randomize);
			builder_start(self);
			builder_spawn_threads(self, IntType(1));
			withOne (obj_builder_thread, DsList(self->thread_list).Value(IntType(0)), self->id)
			{
				for (IntType p = IntType(0); p < self->build_size_total; p++)
				{
					builder_thread_set_pos(self, p);
					builder_set_model(ScopeAny(self));
				}
			}
			
			builder_combine_threads(self);
			builder_spawn_threads(self, IntType(1));
			withOne (obj_builder_thread, DsList(self->thread_list).Value(IntType(0)), self->id)
			{
				for (IntType p = IntType(0); p < self->build_size_total; p++)
				{
					builder_thread_set_pos(self, p);
					builder_generate(ScopeAny(self));
				}
			}
			
			builder_combine_threads(self);
			builder_done(self);
			self->build_randomize = false;
			self->build_single_block = null_;
			self->build_single_stateid = IntType(0);
		}
		
		block_vbuffer_done(self);
	}
	
	void temp_update_display_name(ScopeAny self)
	{
		if (sVar(name) == /*""*/ STR(0))
		{
			sVar(display_name) = text_get({ /*"type"*/ STR(775) + DsList(global::temp_type_name_list).Value(sVar(type)) });
			switch ((IntType)sVar(type))
			{
				case e_temp_type_CHARACTER:
				case e_temp_type_SPECIAL_BLOCK:
				{
					if (sVar(model_file) != null_)
						sVar(display_name) = minecraft_asset_get_name(/*"model"*/ STR(8), idVar(sVar(model_file), name));
					break;
				}
				case e_temp_type_SCENERY:
				{
					if (sVar(scenery) != null_)
						sVar(display_name) = idVar(sVar(scenery), display_name);
					break;
				}
				case e_temp_type_BLOCK:
				{
					sVar(display_name) = minecraft_asset_get_name(/*"block"*/ STR(4), ObjType(obj_block, DsMap(ObjType(obj_minecraft_assets, global::mc_assets)->block_name_map).Value(sVar(block_name)))->name);
					break;
				}
				case e_temp_type_BODYPART:
				{
					if (sVar(model_part) != null_)
						sVar(display_name) = text_get({ /*"librarybodypartof"*/ STR(3296), minecraft_asset_get_name(/*"modelpart"*/ STR(748), idVar(sVar(model_part), name)), minecraft_asset_get_name(/*"model"*/ STR(8), idVar(sVar(model_file), name)) });
					else
						sVar(display_name) = text_get({ /*"librarybodypartunknown"*/ STR(3297) });
					
					break;
				}
				case e_temp_type_MODEL:
				{
					if (sVar(model_file) != null_)
						sVar(display_name) = idVar(sVar(model_file), name);
					else
						if (sVar(model) != null_)
							sVar(display_name) = idVar(sVar(model), display_name);
					
					break;
				}
			}
			
		}
		else
			sVar(display_name) = sVar(name);
		
		withAll (obj_timeline, self->id)
		{
			if (self->temp == self.otherId && self->part_of == null_)
			{
				tl_update_type_name(ScopeAny(self));
				tl_update_display_name(ScopeAny(self));
			}
		}
		
	}
	
	RealType temp_update_model(ScopeAny self, BoolType copy)
	{
		sVar(model_file) = null_;
		if (sInt(model_texture_name_map) == null_)
			sInt(model_texture_name_map) = ds_string_map_create();
		ds_map_clear(sInt(model_texture_name_map));
		if (sInt(model_texture_material_name_map) == null_)
			sInt(model_texture_material_name_map) = ds_string_map_create();
		ds_map_clear(sInt(model_texture_material_name_map));
		if (sInt(model_tex_normal_name_map) == null_)
			sInt(model_tex_normal_name_map) = ds_string_map_create();
		ds_map_clear(sInt(model_tex_normal_name_map));
		if (sInt(model_shape_texture_name_map) == null_)
			sInt(model_shape_texture_name_map) = ds_map_create();
		ds_map_clear(sInt(model_shape_texture_name_map));
		if (sInt(model_shape_texture_material_name_map) == null_)
			sInt(model_shape_texture_material_name_map) = ds_map_create();
		ds_map_clear(sInt(model_shape_texture_material_name_map));
		if (sInt(model_shape_tex_normal_name_map) == null_)
			sInt(model_shape_tex_normal_name_map) = ds_map_create();
		ds_map_clear(sInt(model_shape_tex_normal_name_map));
		if (sInt(model_hide_list) == null_)
			sInt(model_hide_list) = ds_list_create();
		ds_list_clear(sInt(model_hide_list));
		if (sInt(model_shape_hide_list) == null_)
			sInt(model_shape_hide_list) = ds_list_create();
		ds_list_clear(sInt(model_shape_hide_list));
		if (sInt(model_color_name_map) == null_)
			sInt(model_color_name_map) = ds_map_create();
		ds_map_clear(sInt(model_color_name_map));
		if (sVar(type) != e_temp_type_MODEL)
		{
			if (is_undefined(DsMap(ObjType(obj_minecraft_assets, global::mc_assets)->model_name_map).Value(sVar(model_name))))
				return IntType(0);
			VarType tempstatevars, curpatterntype, curfile;
			IntType temptexnamemap, temptexmatnamemap, temptexnormnamemap, tempshapetexnamemap, tempshapetexmatnamemap, tempshapetexnormnamemap, tempcolornamemap, temphidelist, tempshapehidelist;
			tempstatevars = sVar(model_state);
			temptexnamemap = sInt(model_texture_name_map);
			temptexmatnamemap = sInt(model_texture_material_name_map);
			temptexnormnamemap = sInt(model_tex_normal_name_map);
			tempshapetexnamemap = sInt(model_shape_texture_name_map);
			tempshapetexmatnamemap = sInt(model_shape_texture_material_name_map);
			tempshapetexnormnamemap = sInt(model_shape_tex_normal_name_map);
			tempcolornamemap = sInt(model_color_name_map);
			temphidelist = sInt(model_hide_list);
			tempshapehidelist = sInt(model_shape_hide_list);
			withOne (obj_model, DsMap(ObjType(obj_minecraft_assets, global::mc_assets)->model_name_map).Value(sVar(model_name)), self->id)
			{
				curfile = self->file;
				curpatterntype = self->pattern_type;
				if (self->texture_name_map != null_)
					ds_map_merge(temptexnamemap, self->texture_name_map);
				if (self->states_map != null_)
				{
					VarType curstate = ds_map_find_first(self->states_map);
					while (!is_undefined(curstate))
					{
						VarType val = state_vars_get_value(tempstatevars, curstate);
						if (val != /*""*/ STR(0))
						{
							withOne (Object, DsMap(self->states_map).Value(curstate), self->id)
							{
								for (IntType v = IntType(0); v < sReal(value_amount); v++)
								{
									if (val != sVar(value_name).Value(v))
										continue;
									if (sArr(value_file).Value(v) != null_)
										curfile = sArr(value_file).Value(v);
									if (sArr(value_pattern_type).Value(v) != /*""*/ STR(0))
										curpatterntype = sArr(value_pattern_type).Value(v);
									if (sArr(value_texture_name_map).Value(v) != null_)
										ds_map_merge(temptexnamemap, sArr(value_texture_name_map).Value(v), true);
									if (sArr(value_texture_material_name_map).Value(v) != null_)
										ds_map_merge(temptexmatnamemap, sArr(value_texture_material_name_map).Value(v), true);
									if (sArr(value_tex_normal_name_map).Value(v) != null_)
										ds_map_merge(temptexnormnamemap, sArr(value_tex_normal_name_map).Value(v), true);
									if (sArr(value_shape_texture_name_map).Value(v) != null_)
										ds_map_merge(tempshapetexnamemap, sArr(value_shape_texture_name_map).Value(v), true);
									if (sVar(value_shape_texture_material_name_map).Value(v) != null_)
										ds_map_merge(tempshapetexmatnamemap, sVar(value_shape_texture_material_name_map).Value(v), true);
									if (sVar(value_shape_tex_normal_name_map).Value(v) != null_)
										ds_map_merge(tempshapetexnormnamemap, sVar(value_shape_tex_normal_name_map).Value(v), true);
									if (sArr(value_hide_list).Value(v) != null_)
										ds_list_merge(temphidelist, sArr(value_hide_list).Value(v));
									if (sArr(value_shape_hide_list).Value(v) != null_)
										ds_list_merge(tempshapehidelist, sArr(value_shape_hide_list).Value(v));
									if (sArr(value_color_name_map).Value(v) != null_)
										ds_map_merge(tempcolornamemap, sArr(value_color_name_map).Value(v), true);
									break;
								}
							}
							
						}
						curstate = ds_map_find_next(self->states_map, curstate);
					}
					
				}
			}
			
			sVar(model_file) = curfile;
			sVar(pattern_type) = curpatterntype;
		}
		else
			if (sVar(model) != null_)
			{
				sVar(model_file) = idVar(sVar(model), model_file);
				sVar(pattern_type) = idVar(sVar(model), pattern_type);
			}
		
		if (sVar(model_file) != null_ && is_undefined(DsMap(sInt(model_texture_name_map)).Value(/*""*/ STR(0))))
			DsMap(sInt(model_texture_name_map))[/*""*/ STR(0)] = idVar(sVar(model_file), texture_name);
		if (sVar(model_file) != null_ && is_undefined(DsMap(sInt(model_texture_material_name_map)).Value(/*""*/ STR(0))))
			DsMap(sInt(model_texture_material_name_map))[/*""*/ STR(0)] = idVar(sVar(model_file), texture_material_name);
		if (sVar(model_file) != null_ && is_undefined(DsMap(sInt(model_tex_normal_name_map)).Value(/*""*/ STR(0))))
			DsMap(sInt(model_tex_normal_name_map))[/*""*/ STR(0)] = idVar(sVar(model_file), texture_normal_name);
		if (sVar(pattern_type) != /*""*/ STR(0))
			array_add(VarType::CreateRef(global::pattern_update), self->id);
		if (!copy)
			temp_update_model_color(self);
		model_shape_update_color(self);
		temp_update_armor(self->id);
		return 0.0;
	}
	
	RealType temp_update_model_color(ScopeAny self)
	{
		if (self->subAssetId == ID_obj_timeline)
			return IntType(0);
		VarType useblendprev = sVar(model_use_blend_color);
		if (sVar(model_file) != null_ && idVar(sVar(model_file), model_color) != /*"none"*/ STR(878))
		{
			sVar(model_use_blend_color) = true;
			if (!(useblendprev > 0))
				sVar(model_blend_color) = minecraft_get_color(idVar(sVar(model_file), model_color));
		}
		else
		{
			sVar(model_use_blend_color) = false;
			sVar(model_blend_color) = c_white;
		}
		
		sVar(model_blend_color_default) = sVar(model_blend_color);
		return 0.0;
	}
	
	RealType temp_update_model_part(ScopeAny self)
	{
		sVar(model_part) = null_;
		if (sVar(model_file) == null_ || sVar(model_part_name) == /*""*/ STR(0))
			return IntType(0);
		for (IntType p = IntType(0); p < ds_list_size(idInt(sVar(model_file), file_part_list)); p++)
		{
			VarType part = DsList(idInt(sVar(model_file), file_part_list)).Value(p);
			if (ObjType(obj_model_part, part)->name == sVar(model_part_name))
			{
				sVar(model_part) = part;
				break;
			}
		}
		if (sVar(model_part) == null_)
		{
			for (IntType p = IntType(0); p < ds_list_size(idInt(sVar(model_file), file_part_list)); p++)
			{
				VarType part = DsList(idInt(sVar(model_file), file_part_list)).Value(p);
				if (ObjType(obj_model_part, part)->name == default_model_part)
				{
					sVar(model_part) = part;
					sVar(model_part_name) = default_model_part;
					break;
				}
			}
		}
		if (sVar(model_part) == null_ && ds_list_size(idInt(sVar(model_file), file_part_list)) > IntType(0))
		{
			sVar(model_part) = DsList(idInt(sVar(model_file), file_part_list)).Value(IntType(0));
			sVar(model_part_name) = idVar(sVar(model_part), name);
		}
		withAll (obj_timeline, self->id)
		{
			if (self->type != e_tl_type_BODYPART || self->temp != self.otherId)
				continue;
			self->model_part = idVar(self.otherId, model_part);
			self->model_part_name = idVar(self.otherId, model_part_name);
			self->update_matrix = true;
			tl_update_value_types(ScopeAny(self));
		}
		
		return 0.0;
	}
	
	RealType temp_update_model_shape(ScopeAny self)
	{
		if (sInt(model_shape_alpha_map) != null_)
			ds_map_clear(sInt(model_shape_alpha_map));
		if (sInt(model_shape_vbuffer_map) != null_ && ds_map_size(sInt(model_shape_vbuffer_map)) > IntType(0))
		{
			VarType key = ds_map_find_first(sInt(model_shape_vbuffer_map));
			while (!is_undefined(key))
			{
				if (instance_exists(key) && idVar(key, vbuffer_default) != DsMap(sInt(model_shape_vbuffer_map)).Value(key))
					vbuffer_destroy(DsMap(sInt(model_shape_vbuffer_map)).Value(key));
				key = ds_map_find_next(sInt(model_shape_vbuffer_map), key);
			}
			
			ds_map_clear(sInt(model_shape_vbuffer_map));
		}
		if (sVar(model_file) == null_)
			return IntType(0);
		if (idBool(sVar(model_file), has_3d_plane))
		{
			if (sInt(model_shape_alpha_map) == null_)
				sInt(model_shape_alpha_map) = ds_map_create();
		}
		if (sInt(model_shape_vbuffer_map) == null_)
			sInt(model_shape_vbuffer_map) = ds_map_create();
		VarType res = temp_get_model_texobj(self, null_);
		for (IntType p = IntType(0); p < ds_list_size(idInt(sVar(model_file), file_part_list)); p++)
		{
			VarType part = DsList(idInt(sVar(model_file), file_part_list)).Value(p);
			if (ds_list_find_index(sInt(model_hide_list), ObjType(obj_model_part, part)->name) < IntType(0))
			{
				model_part_fill_shape_alpha_map(part, sInt(model_shape_alpha_map), res, sInt(model_texture_name_map), sInt(model_shape_texture_name_map));
				model_part_fill_shape_vbuffer_map(part, sInt(model_shape_vbuffer_map), sInt(model_shape_alpha_map), ObjType(obj_model_part, part)->bend_inherit_angle);
			}
		}
		withAll (obj_timeline, self->id)
			if (self->temp == self.otherId)
				tl_update_model_shape(ScopeAny(self));
		
		return 0.0;
	}
	
	RealType temp_update_model_timeline_parts(ScopeAny self)
	{
		if (sVar(model_file) == null_)
			return IntType(0);
		withAll (obj_timeline, self->id)
		{
			if (self->temp != self.otherId)
				continue;
			for (IntType mp = IntType(0); mp < ds_list_size(idInt(idVar(self->temp, model_file), file_part_list)); mp++)
			{
				if (ObjType(obj_model_part, DsList(idInt(idVar(self->temp, model_file), file_part_list)).Value(mp))->name == self->model_part_name)
				{
					self->model_part = DsList(idInt(idVar(self->temp, model_file), file_part_list)).Value(mp);
					break;
				}
			}
		}
		
		return 0.0;
	}
	
	void temp_update_model_timeline_tree(ScopeAny self, VarType hobj)
	{
		withAll (obj_timeline, self->id)
		{
			if (self->temp != self.otherId || self->part_list == null_)
				continue;
			if (hobj != null_ && !(global::_app->history_undo > 0))
			{
				for (IntType p = IntType(0); p < ds_list_size(self->part_list); p++)
				{
					withOne (Object, DsList(self->part_list).Value(p), self->id)
					{
						for (IntType t = IntType(0); t < ds_list_size(sInt(tree_list)); t++)
						{
							withOne (Object, DsList(sInt(tree_list)).Value(t), self->id)
							{
								if (sVar(part_of) != null_)
									break;
								withOne (obj_history, hobj, self->id)
								{
									self->part_child_save_id[self->part_child_amount] = save_id_get(self.otherId);
									self->part_child_parent_save_id[self->part_child_amount] = save_id_get(idVar(self.otherId, parent));
									self->part_child_parent_tree_index[self->part_child_amount] = t;
									self->part_child_amount++;
								}
								
							}
							
						}
					}
					
				}
			}
			if (hobj != null_ && !(global::_app->history_undo > 0))
			{
				ObjType(obj_history, hobj)->usage_tl_attractor_amount = IntType(0);
				ObjType(obj_history, hobj)->usage_tl_ik_target_amount = IntType(0);
				ObjType(obj_history, hobj)->usage_tl_ik_target_angle_amount = IntType(0);
				ObjType(obj_history, hobj)->usage_kf_ik_target_amount = IntType(0);
				ObjType(obj_history, hobj)->usage_kf_ik_target_angle_amount = IntType(0);
				ObjType(obj_history, hobj)->usage_kf_attractor_amount = IntType(0);
			}
			for (IntType p = IntType(0); p < ds_list_size(self->part_list); p++)
			{
				withOne (Object, DsList(self->part_list).Value(p), self->id)
				{
					if (ds_list_size(sInt(keyframe_list)) == IntType(0))
					{
						BoolType unused = true;
						if (idVar(sVar(temp), model_file) != null_ && ds_list_find_index(idInt(sVar(temp), model_hide_list), sVar(model_part_name)) == -IntType(1))
						{
							for (IntType mp = IntType(0); mp < ds_list_size(idInt(idVar(sVar(temp), model_file), file_part_list)); mp++)
							{
								if (ObjType(obj_model_part, DsList(idInt(idVar(sVar(temp), model_file), file_part_list)).Value(mp))->name == sVar(model_part_name))
								{
									unused = false;
									break;
								}
							}
						}
						if (unused)
						{
							for (IntType t = IntType(0); t < ds_list_size(sInt(tree_list)); t++)
							{
								withOne (Object, DsList(sInt(tree_list)).Value(t), self->id)
								{
									if (sVar(part_of) != null_)
										break;
									tl_set_parent(self, { idVar(self.otherId, part_of) });
									t--;
								}
								
							}
							if (!(global::_app->history_redo > 0))
								if (history_save_part_usage_tl(self->id, hobj))
									unused = false;
							if (unused)
							{
								p--;
								tl_remove_clean(self);
								continue;
							}
						}
					}
					sVar(model_part) = null_;
					tl_set_parent(self, { self.otherId });
					tl_update_value_types(self);
					tl_update_type_name(self);
					tl_update_display_name(self);
				}
				
			}
			withAll (obj_timeline, self->id)
				if (self->delete_ready)
					instance_destroy(ScopeAny(self));
			
			if (idVar(self->temp, model_file) != null_)
			{
				ds_list_clear(self->part_list);
				for (IntType mp = IntType(0); mp < ds_list_size(idInt(idVar(self->temp, model_file), file_part_list)); mp++)
				{
					VarType part;
					BoolType tlexists;
					part = DsList(idInt(idVar(self->temp, model_file), file_part_list)).Value(mp);
					tlexists = false;
					if (ds_list_find_index(idInt(self->temp, model_hide_list), ObjType(obj_model_part, part)->name) > -IntType(1))
						continue;
					withAll (obj_timeline, self->id)
					{
						if (self->part_of == self.otherId && self->model_part_name == ObjType(obj_model_part, part)->name)
						{
							ds_list_add({ ObjType(obj_timeline, self.otherId)->part_list, self->id });
							self->lock_bend = ObjType(obj_model_part, part)->lock_bend;
							self->part_mixing_shapes = ObjType(obj_model_part, part)->part_mixing_shapes;
							tlexists = true;
							break;
						}
					}
					
					if (!tlexists)
						ds_list_add({ self->part_list, tl_new_part(self, part) });
				}
				tl_update_part_list(ScopeAny(self), idVar(self->temp, model_file), self->id);
			}
			tl_update_type_name(ScopeAny(self));
			tl_update_display_name(ScopeAny(self));
			self->update_matrix = true;
		}
		
	}
	
	void temp_update_rot_point(ScopeAny self)
	{
		sVar(rot_point) = point3D(IntType(0), IntType(0), IntType(0));
		VarType rep = ((sVar(block_repeat_enable) > 0) ? sVar(block_repeat) : VarType(vec3(IntType(1))));
		switch ((IntType)sVar(type))
		{
			case e_temp_type_SCENERY:
			{
				if (sVar(scenery) == null_ || !idBool(sVar(scenery), ready))
					break;
				sVar(rot_point)[X_] = (rep.Value(X_) * idVec(sVar(scenery), scenery_size).Real(X_) * block_size_) / 2.0;
				sVar(rot_point)[Y_] = (rep.Value(Y_) * idVec(sVar(scenery), scenery_size).Real(Y_) * block_size_) / 2.0;
				break;
			}
			
			case e_temp_type_BLOCK:
			{
				sVar(rot_point)[X_] = (rep.Value(X_) * block_size_) / 2.0;
				sVar(rot_point)[Y_] = (rep.Value(Y_) * block_size_) / 2.0;
				break;
			}
			
			case e_temp_type_MODEL:
			{
				if (sVar(model) != null_ && idInt(sVar(model), model_format) == e_model_format_BLOCK)
				{
					sVar(rot_point)[X_] = block_size_ / 2.0;
					sVar(rot_point)[Y_] = block_size_ / 2.0;
				}
				break;
			}
			
			case e_temp_type_ITEM:
			{
				sVar(rot_point)[X_] = item_size / 2.0;
				sVar(rot_point)[Y_] = 0.5 * bool_to_float(sVar(item_3d));
				break;
			}
			
			case e_temp_type_TEXT:
			{
				sVar(rot_point)[Y_] = 0.5 * bool_to_float(sVar(text_3d));
				break;
			}
			
		}
		
		if (type_is_shape(sVar(type)))
			sVar(rot_point)[Z_] = -IntType(8);
		withAll (obj_timeline, self->id)
			if (self->temp == self.otherId)
				tl_update_rot_point(ScopeAny(self));
		
	}
	
	void temp_update_shape(ScopeAny self)
	{
		if (sVar(shape_vbuffer) > 0)
			vbuffer_destroy(sVar(shape_vbuffer));
		RealType shapetype, rad, thflip, tvflip;
		VecType tex1, tex2;
		shapetype = (self->id == global::_app->bench_settings ? VarType(sReal(shape_type)) : sVar(type) - e_temp_type_CUBE);
		rad = IntType(8);
		thflip = negate(sVar(shape_tex_hmirror));
		tvflip = negate(sVar(shape_tex_vmirror));
		if (sVar(shape_invert) > 0)
			thflip *= -1.0;
		tex1 = point2D(sVar(shape_tex_hoffset), sVar(shape_tex_voffset));
		tex2 = point2D(sVar(shape_tex_hoffset) + sVar(shape_tex_hrepeat), sVar(shape_tex_voffset) + sVar(shape_tex_vrepeat));
		if (thflip < IntType(0))
		{
			tex1.Real(X_) = 1.0 - tex1.Real(X_);
			tex2.Real(X_) = 1.0 - tex2.Real(X_);
		}
		if (tvflip < IntType(0))
		{
			tex1.Real(Y_) = 1.0 - tex1.Real(Y_);
			tex2.Real(Y_) = 1.0 - tex2.Real(Y_);
		}
		switch ((IntType)shapetype)
		{
			case e_shape_type_SURFACE:
			{
				sVar(shape_vbuffer) = vbuffer_create_surface(rad, tex1, tex2, sVar(shape_invert));
				break;
			}
			case e_shape_type_CUBE:
			{
				sVar(shape_vbuffer) = vbuffer_create_cube(rad, tex1, tex2, thflip, tvflip, sVar(shape_invert), sVar(shape_tex_mapped));
				break;
			}
			case e_shape_type_CONE:
			{
				sVar(shape_vbuffer) = vbuffer_create_cone(rad, tex1, tex2, thflip, tvflip, sVar(shape_detail), sVar(shape_closed), sVar(shape_invert), sVar(shape_tex_mapped));
				break;
			}
			case e_shape_type_CYLINDER:
			{
				sVar(shape_vbuffer) = vbuffer_create_cylinder(rad, tex1, tex2, thflip, tvflip, sVar(shape_detail), sVar(shape_closed), sVar(shape_invert), sVar(shape_tex_mapped));
				break;
			}
			case e_shape_type_SPHERE:
			{
				sVar(shape_vbuffer) = vbuffer_create_sphere(rad, tex1, tex2, sVar(shape_detail), sVar(shape_invert));
				break;
			}
		}
		
	}
	
}
