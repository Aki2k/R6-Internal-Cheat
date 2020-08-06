#pragma once
#include <cstdint>

#include "vec3_t.hpp"
#include "memory.h"
#include "offsets.h"
#include "math.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

class camera
{
public:
	camera();
	vec3_t w2s(vec3_t position);

private:

	void update_values();

	mem::memory mem{};
	uintptr_t render{};
	uintptr_t game_render{};
	uintptr_t engine_link{};
	uintptr_t engine{};
	uintptr_t cam{};

	float fov_y{};
	float fov_x{};

	vec3_t forward{},
		up{},
		right{},
		translation{};

};