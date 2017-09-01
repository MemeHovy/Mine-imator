/// tl_set_parent(parent, [index])
/// @desc Sets the parent
/// @arg parent
/// @arg [index]

if (parent != null)
	ds_list_delete_value(parent.tree_list, id)

parent = argument[0]

var index;
if (argument_count > 1 && argument[1] >= 0)
	index = argument[1]
else
	index = ds_list_size(parent.tree_list)

ds_list_insert(parent.tree_list, index, id)

update_matrix = true
