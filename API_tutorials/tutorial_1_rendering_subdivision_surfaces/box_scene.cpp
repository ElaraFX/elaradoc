/////////////////////////////////////////////////////
// ESS Sample
//
// Copyright 2013-2016 Rendease Co., Ltd. All Rights Reserved.
//

#include <ei.h>									// include header of ESS style APIs

int main(int argc, char* argv[])
{
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
			ei_tab_add_point(-0.179573f, -7.973234f, -16.724060f);
			ei_tab_add_point(-7.068787f,  4.344949f, -17.619093f);
			ei_tab_add_point(-0.179573f,  0.527515f, -11.457443f);
			ei_tab_add_point(0.179573f, -0.527514f, -28.742058f);
			ei_tab_add_point(7.068787f, -4.344948f, -22.580408f);
			ei_tab_add_point(0.179573f,  7.973235f, -23.475441f);
			ei_tab_add_point(7.068787f,  4.155800f, -17.313791f);
		ei_end_tab();
		ei_param_array("face_counts", ei_tab(EI_TYPE_INDEX, 1));
			ei_tab_add_index(4);				// all faces are of 4 vertices
			ei_tab_add_index(4);
			ei_tab_add_index(4);
			ei_tab_add_index(4);
			ei_tab_add_index(4);
			ei_tab_add_index(4);
		ei_end_tab();
		ei_param_array("face_indices", ei_tab(EI_TYPE_INDEX, 1));
			ei_tab_add_index(0); ei_tab_add_index(1); ei_tab_add_index(3); ei_tab_add_index(2);
			ei_tab_add_index(1); ei_tab_add_index(5); ei_tab_add_index(7); ei_tab_add_index(3);
			ei_tab_add_index(5); ei_tab_add_index(4); ei_tab_add_index(6); ei_tab_add_index(7);
			ei_tab_add_index(4); ei_tab_add_index(0); ei_tab_add_index(2); ei_tab_add_index(6);
			ei_tab_add_index(4); ei_tab_add_index(5); ei_tab_add_index(1); ei_tab_add_index(0);
			ei_tab_add_index(2); ei_tab_add_index(3); ei_tab_add_index(7); ei_tab_add_index(6);
		ei_end_tab();
		ei_declare_color_array("geom_color", EI_FACEVARYING, EI_NULL_TAG);	// declare array of data elements
		ei_param_array("geom_color", ei_tab(EI_TYPE_COLOR, 1));				// set the data values
			ei_tab_add_color(0.0f, 1.0f, 1.0f);
			ei_tab_add_color(1.0f, 0.0f, 1.0f);
			ei_tab_add_color(1.0f, 1.0f, 0.0f);
			ei_tab_add_color(1.0f, 0.0f, 0.0f);
			ei_tab_add_color(0.0f, 1.0f, 0.0f);
			ei_tab_add_color(0.0f, 0.0f, 1.0f);
			ei_tab_add_color(1.0f, 1.0f, 1.0f);
			ei_tab_add_color(0.5f, 1.0f, 0.5f);
			ei_tab_add_color(1.0f, 0.5f, 0.5f);
			ei_tab_add_color(0.5f, 0.5f, 1.0f);
			ei_tab_add_color(1.0f, 0.0f, 0.5f);
			ei_tab_add_color(0.5f, 1.0f, 0.0f);
			ei_tab_add_color(0.0f, 1.0f, 0.5f);
			ei_tab_add_color(0.5f, 0.0f, 1.0f);
			ei_tab_add_color(1.0f, 0.5f, 0.0f);
			ei_tab_add_color(0.0f, 0.5f, 1.0f);
			ei_tab_add_color(0.3f, 0.8f, 1.0f);
			ei_tab_add_color(1.0f, 0.5f, 0.7f);
			ei_tab_add_color(0.2f, 1.0f, 0.6f);
			ei_tab_add_color(1.0f, 0.2f, 0.9f);
			ei_tab_add_color(0.4f, 0.7f, 1.0f);
			ei_tab_add_color(1.0f, 0.3f, 0.3f);
			ei_tab_add_color(0.8f, 0.6f, 0.2f);
			ei_tab_add_color(0.1f, 0.9f, 1.0f);
		ei_end_tab();
		ei_declare_index_array("geom_color_idx", EI_FACEVARYING, EI_NULL_TAG);						// declare array of indices
		ei_param_array("geom_color_idx", ei_tab(EI_TYPE_INDEX, 1));									// set the indices
			ei_tab_add_index(0); ei_tab_add_index(3); ei_tab_add_index(9); ei_tab_add_index(6);		// the number of data elements must 
			ei_tab_add_index(7); ei_tab_add_index(10); ei_tab_add_index(15); ei_tab_add_index(12);	// match the sum of all face counts
			ei_tab_add_index(13); ei_tab_add_index(16); ei_tab_add_index(21); ei_tab_add_index(18);
			ei_tab_add_index(19); ei_tab_add_index(22); ei_tab_add_index(4); ei_tab_add_index(1);
			ei_tab_add_index(5); ei_tab_add_index(23); ei_tab_add_index(17); ei_tab_add_index(11);
			ei_tab_add_index(20); ei_tab_add_index(2); ei_tab_add_index(8); ei_tab_add_index(14);
		ei_end_tab();
		ei_param_int("subdiv_iterations", 4);	// subdivide the mesh 4 times
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

	ei_render("world", "caminst1", "opt");		// render frame command

	return 0;
}
