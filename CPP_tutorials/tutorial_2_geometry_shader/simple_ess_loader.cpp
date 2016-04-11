/////////////////////////////////////////////////////
// Module initialization and cleanup.
//
// Copyright 2015 Rendease, Ltd. All Rights Reserved.
//

#define EI_NO_OSL_INTEROP 1

#include <ei_shaderx.h>

// A simple procedural which loads ESS proxy.
//
geometry (simple_ess_loader)

	enum
	{
		e_filename = 0, 
		e_root_name, 
	};

	static void parameters()
	{
		declare_token(filename, NULL);
		declare_token(root_name, NULL);
	}

	static void init()
	{
	}

	static void exit()
	{
	}

	void init_node()
	{
	}

	void exit_node()
	{
	}

	void main(void *arg)
	{
		ei_sub_context();

		eiToken filename = eval_token(filename);
		eiToken root_name = eval_token(root_name);

		ei_parse(filename.str, EI_TRUE);

		// set the root node for current procedural object
		geometry_root(root_name.str);

		ei_end_sub_context();
	}

end_shader (simple_ess_loader)
