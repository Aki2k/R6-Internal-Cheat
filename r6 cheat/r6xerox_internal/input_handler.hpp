#pragma once
#include <thread>
#include <atomic>
#include "unlock_all.h"
#include "gun_mod.h"
#include "player.h"
#include "esp.h"

namespace input_handler
{
	inline std::thread input_thread;
	inline esp::spotted spotted_esp;
	inline esp::draw_esp draw_esp;
	inline unlock_all::unlock_all unlockall;
	inline gun_mod::no_recoil no_recoil;
	inline player::player_mod::glow_effects glow;
	inline gun_mod::damage_mod damage_mod;

	namespace elements 
	{
		namespace toggle
		{
			inline std::atomic<bool> spotted_esp_button{}, 
				unlock_all_button{},
				no_recoil_button{},
				glow_button{},
				damage_mod{},
				esp_health_bar{},
				esp_distance{},
				esp_health{},
				esp_corners{};
		}

		namespace slider
		{
			inline std::atomic<float> glow_red{},
				glow_blue{},
				glow_green{},
				glow_alpha{},
				glow_distance{},
				glow_opacity{},
				no_recoil{},
				damage_mod{},
				speed_slider{};
		}

		namespace element_name
		{
			inline std::atomic<const char*> spotted_button{ "##spotted_button" },
				unlock_all_button{ "##unlock_all_button" },
				no_recoil_button{ "##no_recoil_button" },
				glow_button{ "##glow_button" },
				glow_red{ "red" },
				glow_blue{ "blue" },
				glow_green{ "green" },
				glow_distance{ "distance" },
				glow_alpha{ "alpha" },
				glow_opacity{ "opacity" },
				no_recoil{ "recoil" },
				damage_mod_button{ "##modifier_button" },
				damage_slider{ "modifier" },
				speed_button_name{ "##speed_button" },
				esp_health_bar{"##display_health_bar"},
				esp_corners{"##display_corners"},
				esp_display_health{"##display_health"},
				esp_display_distance{"##display_distance"};
		}
	}

	inline void input_handler_func()
	{

		//loop forever and interface with input
		while(true)
		{
			spotted_esp.input_interface(elements::toggle::spotted_esp_button);
			unlockall.input_interface(elements::toggle::unlock_all_button);
			no_recoil.input_interface(elements::toggle::no_recoil_button);

			glow.input_handler(elements::toggle::glow_button,
				elements::slider::glow_red,
				elements::slider::glow_blue,
				elements::slider::glow_green,
				elements::slider::glow_distance,
				elements::slider::glow_alpha,
				elements::slider::glow_opacity
			);

			damage_mod.input_interface(elements::toggle::damage_mod, elements::slider::damage_mod);

			if (GetAsyncKeyState(VK_INSERT))
				display::inside_menu = !display::inside_menu;
			Sleep(250);
		}
	}

	inline void init()
	{
		input_thread = std::thread(&input_handler_func);
		input_thread.detach();
	}
}