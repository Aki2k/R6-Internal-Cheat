#pragma once
#include <math.h>
#include "vec3_t.hpp"

namespace math {

	inline float dot_product(vec3_t src, vec3_t dst)
	{
		return src.x * dst.x + src.y * dst.y + src.z * dst.z;
	}

	inline vec3_t subtract(vec3_t one, vec3_t two)
	{
		vec3_t temp;
		temp.x = one.x - two.x;
		temp.y = one.y - two.y;
		temp.z = one.z - two.z;
		return temp;
	}

	inline vec3_t multiply(vec3_t one, float multi_me)
	{
		vec3_t temp;
		temp.x = one.x * multi_me;
		temp.y = one.y * multi_me;
		temp.z = one.z * multi_me;
		return temp;
	}

	inline vec3_t w2s(
		vec3_t position,
		vec3_t translation,
		vec3_t forward,
		vec3_t up,
		vec3_t right,
		float fovx,
		float fovy,
		unsigned screen_width,
		unsigned screen_height
	)
	{
		vec3_t t = subtract(position, translation);
		float z = dot_product(t, multiply(forward, -1));
		return vec3_t {
			screen_width / 2 * (1 + dot_product(t, right) / fovx / z),
			screen_height / 2 * (1 - dot_product(t, up) / fovy / z),
			z
		};
	}
}