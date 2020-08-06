#pragma once
#include <vector>
#include <atomic>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "player.h"
#include "camera.h"

namespace esp {

	inline std::atomic<bool> currently_spotting{}, outline_enabled{};

	class spotted {

	public:
		spotted();
		void input_interface(bool toggle);
	private:
		void enable();
		void disable();

		const uint8_t spotted_enable_icon_bytes[7] = {
			0x80,
			0xB9,
			0x34,
			0x05,
			0x00,
			0x00,
			0x01
		};

		const uint8_t spotted_disable_icon_bytes[7] = {
			0x80,
			0xB9,
			0x34,
			0x05,
			0x00,
			0x00,
			0x00
		};

		const uint8_t spotted_enable_name_bytes[7] = {
			0x80,
			0xBB,
			0x34,
			0x05,
			0x00,
			0x00,
			0x01
		};

		const uint8_t spotted_disable_name_bytes[7] = {
			0x80,
			0xBB,
			0x34,
			0x05,
			0x00,
			0x00,
			0x00
		};

	};


	class draw_esp {

	public:
		draw_esp() {};
		void box_esp();
		void health_bar();
		void display_distance();

	private:
		player::player_list player_list{};
		mem::memory mem{};
		camera cam{};
		std::vector<uintptr_t> players{};
		const ImVec4 red = { 
			0.65,
			0,
			0,
			1 
		};

		const ImVec4 black ={
			0,
			0,
			0,
			1
		};

		const ImVec4 green = {
			0.03,
			0.81,
			0.14,
			1
		};

		const ImVec4 blue = {
			0.21960784313,
			0.56470588235,
			0.90980392156,
			1.0
		};
	};
}