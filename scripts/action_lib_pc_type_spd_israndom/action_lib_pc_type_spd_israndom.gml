/// action_lib_pc_type_spd_israndom(israndom)
/// @arg israndom

function action_lib_pc_type_spd_israndom(israndom)
{
	if (!history_undo && !history_redo)
		history_set_var(action_lib_pc_type_spd_israndom, ptype_edit.spd_israndom[axis_edit], israndom, false)
	
	ptype_edit.spd_israndom[axis_edit] = israndom
}
