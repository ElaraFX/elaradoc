/////////////////////////////////////////////////////
// Light filter with distance falloffs
//
// Copyright 2013-2016 Rendease Co., Ltd. All Rights Reserved.
//

#include <ei_shaderx.h>

// A simple light filter which adds distance falloffs.
//
light (simple_light_filter)

	enum
	{
		e_use_near_atten = 0, 
		e_near_start, 
		e_near_stop, 
		e_use_far_atten, 
		e_far_start, 
		e_far_stop, 
	};

	static void parameters()
	{
		declare_bool(use_near_atten, EI_FALSE);
		declare_scalar(near_start, 10.0f);
		declare_scalar(near_stop, 100.0f);
		declare_bool(use_far_atten, EI_FALSE);
		declare_scalar(far_start, 500.0f);
		declare_scalar(far_stop, 1000.0f);
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
		eiScalar atten = (eiScalar)EI_PI;

		const eiBool use_near_atten = eval_bool(use_near_atten);
		const eiBool use_far_atten = eval_bool(use_far_atten);

		if (use_near_atten || use_far_atten)
		{
			const eiScalar d = len(Ps);

			if (use_near_atten)
			{
				const eiScalar near_start = eval_scalar(near_start);
				const eiScalar near_stop = eval_scalar(near_stop);

				atten *= smoothstep(near_start, near_stop, d);
			}

			if (use_far_atten)
			{
				const eiScalar far_start = eval_scalar(far_start);
				const eiScalar far_stop = eval_scalar(far_stop);

				atten *= (1.0f - smoothstep(far_start, far_stop, d));
			}
		}

		eiColor *light_color = (eiColor *)arg;
		(*light_color) *= atten;
	}

end_shader (simple_light_filter)
