/// action_background_fog_sky(show)
/// @arg show

function action_background_fog_sky(show)
{
	if (!history_undo && !history_redo)
	{
		if (action_tl_select_single(null, e_tl_type.BACKGROUND))
		{
			tl_value_set_start(action_background_fog_sky, true)
			tl_value_set(e_value.BG_FOG_SKY, show, false)
			tl_value_set_done()
			return 0
		}
		
		history_set_var(action_background_fog_sky, background_fog_sky, show, false)
	}
	
	background_fog_sky = show
}
