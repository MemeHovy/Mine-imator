/// tab_properties_project()

// Project name
tab.project.tbx_name.text = project_name
tab_control(48)
if (draw_textfield("projectname", dx, dy, dw, 28, project_name, tab.project.tbx_name, null, "", "top"))
{
	project_changed = true
	project_name = tab.project.tbx_name.text
}
tab_next()

// Project author
tab.project.tbx_author.text = project_author
tab_control(48)
if (draw_textfield("projectauthor", dx, dy, dw, 28, project_author, tab.project.tbx_author, null, "", "top"))
{
	project_changed = true
	project_author = tab.project.tbx_author.text
}
tab_next()

// Project description
tab.project.tbx_description.text = project_description
tab_control(108)
if (draw_textfield("projectdescription", dx, dy, dw, 88, project_description, tab.project.tbx_description, null, "", "top"))
{
	project_changed = true
	project_description = tab.project.tbx_description.text
}
tab_next()

// Project location
tab_control(40)
draw_label(text_get("newprojectlocation"), dx, dy + 20, fa_left, fa_bottom, c_text_secondary, a_text_secondary, font_emphasis)

var directory = "...\\" + directory_name(project_folder) + filename_name(filename_dir(project_file));

draw_label(directory, dx, dy + 38, fa_left, fa_bottom, c_text_main, a_text_main, font_value)
if (draw_button_icon("newprojectchangefolder", dx + dw - 20, dy + 10, 24, 24, false, icons.BROWSE, null, null, "tooltipopenfolder"))
	action_toolbar_open_folder()

tab_next()

// Video size
if (project_video_template = 0)
	text = text_get("projectvideosizecustom")
else
	text = text_get("projectvideosizetemplate" + project_video_template.name) + " (" + string(project_video_template.width) + "x" + string(project_video_template.height) + ")"

tab_control_menu()
draw_button_menu("projectvideosize", e_menu.LIST, dx, dy, dw, 28, project_video_template, text, action_project_video_template, null, null)
tab_next()

// Custom
if (project_video_template = 0)
{
	tab_control(28)
	draw_textfield_num("projectvideosizecustomwidth", dx, dy, 86, project_video_width, 1, 1, no_limit, 1280, 1, tab.project.tbx_video_size_custom_width, action_project_video_width)
	tab_next()
	
	tab_control(28)
	draw_textfield_num("projectvideosizecustomheight", dx, dy, 86, project_video_height, 1, 1, no_limit, 720, 1, tab.project.tbx_video_size_custom_height, action_project_video_width)
	tab_next()
	
	tab_control_switch()
	draw_switch("projectvideosizecustomkeepaspectratio", dx, dy, project_video_keep_aspect_ratio, action_project_video_keep_aspect_ratio, true)
	tab_next()
}

// Tempo
tab_control_meter()
draw_meter("projecttempo", dx, dy, dw, project_tempo, 50, 1, 100, 24, 1, tab.project.tbx_tempo, action_project_tempo)
tab_next()
