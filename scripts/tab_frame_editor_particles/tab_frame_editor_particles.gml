/// tab_frame_editor_particles()

var text;

// Spawn
tab_control_checkbox()
draw_switch("frameeditorparticlesspawn", dx, dy, tl_edit.value[e_value.SPAWN], action_tl_frame_spawn, true)
tab_next()

// Freeze
tab_control_checkbox()
draw_switch("frameeditorparticlesfreeze", dx, dy, tl_edit.value[e_value.FREEZE], action_tl_frame_freeze, false)
tab_next()

// Clear
tab_control_checkbox()
draw_switch("frameeditorparticlesclear", dx, dy, tl_edit.value[e_value.CLEAR], action_tl_frame_clear, false)
tab_next()

// Custom seed
tab_control_checkbox()
draw_switch("frameeditorparticlescustomseed", dx, dy, tl_edit.value[e_value.CUSTOM_SEED], action_tl_frame_custom_seed, false)
tab_next()

if (tl_edit.value[e_value.CUSTOM_SEED])
{
	// Seed
	tab_control_dragger()
	draw_dragger("frameeditorparticlesseed", dx, dy, dw, tl_edit.value[e_value.SEED], 0.1, 0, 32000, 0, 1, tab.particles.tbx_seed, action_tl_frame_seed)
	tab_next()
}

// Attractor
if (tl_edit.value[e_value.ATTRACTOR] != null)
	text = tl_edit.value[e_value.ATTRACTOR].display_name
else
	text = text_get("listnone")

tab_control_menu(28)
draw_button_menu("frameeditorparticlesattractor", e_menu.TIMELINE, dx, dy, dw, 28, tl_edit.value[e_value.ATTRACTOR], text, action_tl_frame_attractor)
tab_next()

// Force
if (tl_edit.value[e_value.ATTRACTOR])
{
	tab_control_dragger()
	draw_dragger("frameeditorparticlesforce", dx, dy, 86, tl_edit.value[e_value.FORCE], 1 / 50, -no_limit, no_limit, 1, 0, tab.particles.tbx_force, action_tl_frame_force)
	tab_next()
}
