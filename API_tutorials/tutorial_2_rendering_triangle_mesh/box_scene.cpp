/////////////////////////////////////////////////////
// ESS Sample
//
// Copyright 2013-2016 Rendease Co., Ltd. All Rights Reserved.
//

#include <ei.h>									// include header of ESS style APIs

int main(int argc, char* argv[])
{
	ei_context();								// create rendering context

	ei_verbose("info");							// set verbosity level to info

	ei_link("liber_shader");					// link to standard C++ shader DSO

	ei_node("options", "opt");					// create a rendering options node
		ei_param_int("min_samples", 0);
		ei_param_int("max_samples", 16);
		ei_param_enum("filter", "gaussian");
		ei_param_scalar("filter_size", 3.0f);
		ei_param_scalar("display_gamma", 2.2f);	// by default, the display gamma is off
	ei_end_node();

	ei_node("outvar", "var1");
		ei_param_token("name", "color");
		ei_param_enum("type", "color");
		ei_param_bool("use_gamma", EI_TRUE);	// apply display gamma for this output
	ei_end_node();

	ei_node("output", "out1");					// create an output in PNG foramt
		ei_param_token("filename", "D:/box_scene.0001.png");
		ei_param_enum("data_type", "rgb");
		ei_param_array("var_list", ei_tab(EI_TYPE_TAG_NODE, 1));
			ei_tab_add_node("var1");
		ei_end_tab();
	ei_end_node();

	ei_node("camera", "cam1");					// create perspective camera
		ei_param_array("output_list", ei_tab(EI_TYPE_TAG_NODE, 1));
			ei_tab_add_node("out1");
		ei_end_tab();
		ei_param_scalar("focal", 100.0f);
		ei_param_scalar("aperture", 144.724029f);
		ei_param_scalar("aspect", 1.333333f);
		ei_param_int("res_x", 320);
		ei_param_int("res_y", 240);
	ei_end_node();

	ei_node("instance", "caminst1");			// create camera instance
		ei_param_node("element", "cam1");
	ei_end_node();

	ei_node("pointlight", "light1");			// create a point light
		ei_param_scalar("intensity", 100000.0f);
		ei_param_color("color", 1.0f, 1.0f, 1.0f);
	ei_end_node();

	ei_node("instance", "lightinst1");			// create light instance
		ei_param_node("element", "light1");
		ei_param_matrix("transform", 
			1.0f, 0.0f, 0.0f, 0.0f, 
			0.0f, 1.0f, 0.0f, 0.0f, 
			0.0f, 0.0f, 1.0f, 0.0f, 
			141.375732f, 83.116005f, 35.619434f, 1.0f);
		// motion transform must be set even when there's no motion blur
		ei_param_matrix("motion_transform", 
			1.0f, 0.0f, 0.0f, 0.0f, 
			0.0f, 1.0f, 0.0f, 0.0f, 
			0.0f, 0.0f, 1.0f, 0.0f, 
			141.375732f, 83.116005f, 35.619434f, 1.0f);
	ei_end_node();

	ei_node("plastic", "plastic_shader");		// create plastic surface shader
		ei_param_color("diffuse_color", 0.7f, 0.2f, 0.3f);
		ei_param_scalar("specular_weight", 0.8f);
		ei_param_scalar("specular_roughness", 0.1f);
	ei_end_node();

	ei_node("osl_shadergroup", "plastic_shader_group");
		ei_param_array("nodes", ei_tab(EI_TYPE_TAG_NODE, 1));
			ei_tab_add_node("plastic_shader");
		ei_end_tab();
	ei_end_node();

	ei_node("material", "mtl");
		ei_param_node("surface_shader", "plastic_shader_group");
	ei_end_node();

	ei_node("poly", "obj1");					// create triangle mesh
		ei_param_array("pos_list", ei_tab(EI_TYPE_POINT, 1));
			ei_tab_add_point(-7.068787f, -4.155799f, -22.885710f);
			ei_tab_add_point(-0.179573 -7.973234 -16.724060);
			ei_tab_add_point(-7.068787  4.344949 -17.619093);
			ei_tab_add_point(-0.179573  0.527515 -11.457443);
			ei_tab_add_point( 0.179573 -0.527514 -28.742058);
			ei_tab_add_point( 7.068787 -4.344948 -22.580408);
			ei_tab_add_point( 0.179573  7.973235 -23.475441);
			ei_tab_add_point( 7.068787  4.155800 -17.313791);
		ei_end_tab();
		ei_param_array("triangle_list", ei_tab(EI_TYPE_INDEX, 1));
			ei_tab_add_index(0); ei_tab_add_index(1); ei_tab_add_index(3);
			ei_tab_add_index(0); ei_tab_add_index(3); ei_tab_add_index(2);
			ei_tab_add_index(1); ei_tab_add_index(5); ei_tab_add_index(7);
			ei_tab_add_index(1); ei_tab_add_index(7); ei_tab_add_index(3);
			ei_tab_add_index(5); ei_tab_add_index(4); ei_tab_add_index(6);
			ei_tab_add_index(5); ei_tab_add_index(6); ei_tab_add_index(7);
			ei_tab_add_index(4); ei_tab_add_index(0); ei_tab_add_index(2);
			ei_tab_add_index(4); ei_tab_add_index(2); ei_tab_add_index(6);
			ei_tab_add_index(4); ei_tab_add_index(5); ei_tab_add_index(1);
			ei_tab_add_index(4); ei_tab_add_index(1); ei_tab_add_index(0);
			ei_tab_add_index(2); ei_tab_add_index(3); ei_tab_add_index(7);
			ei_tab_add_index(2); ei_tab_add_index(7); ei_tab_add_index(6);
		ei_end_tab();
	ei_end_node();

	ei_node("instance", "inst1");				// create object instance
		ei_param_node("element", "obj1");
		ei_param_array("mtl_list", ei_tab(EI_TYPE_TAG_NODE, 1));
			ei_tab_add_node("mtl");
		ei_end_tab();
	ei_end_node();

	ei_node("instgroup", "world");				// create root world
		ei_param_array("instance_list", ei_tab(EI_TYPE_TAG_NODE, 1));
			ei_tab_add_node("caminst1");
			ei_tab_add_node("lightinst1");
			ei_tab_add_node("inst1");
		ei_end_tab();
	ei_end_node();

	ei_render_prepare();
	ei_render_run("world", "caminst1", "opt");	// render frame command
	ei_render_cleanup();

	ei_end_context();							// destroy rendering context

	return 0;
}
