/// app_update_lists()
/// @desc Execute scripts in clicked item lists

if (list_item_script != null)
{
	if (list_item_script_value = null)
		script_execute(list_item_script)
	else
		script_execute(list_item_script, list_item_script_value)
	
	list_item_script = null
	list_item_script_value = null
	list_item_value = null
}
