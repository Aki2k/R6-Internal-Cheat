#include "camera.h"
#include "vec3_t.hpp"
#include "imgui/imgui_impl_win32.h"
camera::camera()
{
	render = mem::read<uintptr_t>(mem.get_base_addr() + offsets::base_offsets::camrea_manager);
	game_render = mem::read<uintptr_t>(render);
	engine_link = mem::read<uintptr_t>(game_render + offsets::camrea_offsets::engine_link);
	engine = mem::read<uintptr_t>(engine_link + offsets::camrea_offsets::engine);
	cam = mem::read<uintptr_t>(engine + offsets::camrea_offsets::camera);
	update_values();
}


void camera::update_values()
{
	cam = mem::read<uintptr_t>(engine + offsets::camrea_offsets::camera);
	fov_x = mem::read<float>(cam + offsets::camrea_offsets::fov_x);
	fov_y = mem::read<float>(cam + offsets::camrea_offsets::fov_y);
	forward = mem::read<vec3_t>(cam + offsets::camrea_offsets::forward);
	up = mem::read<vec3_t>(cam + offsets::camrea_offsets::up);
	right = mem::read<vec3_t>(cam + offsets::camrea_offsets::right);
	translation = mem::read<vec3_t>(cam + offsets::camrea_offsets::translation);
}

vec3_t camera::w2s(vec3_t pos)
{
	update_values();
	return math::w2s(
		pos,
		translation,
		forward,
		up,
		right,
		fov_x,
		fov_y,
		ImGui::GetIO().DisplaySize.x,
		ImGui::GetIO().DisplaySize.y
	);
}