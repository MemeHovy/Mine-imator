/// action_lib_pc_type_alpha_israndom(israndom)
/// @arg israndom

function action_lib_pc_type_alpha_israndom(israndom)
{
	if (!history_undo && !history_redo)
		history_set_var(action_lib_pc_type_alpha_israndom, ptype_edit.alpha_israndom, israndom, false)
	
	ptype_edit.alpha_israndom = israndom
}
