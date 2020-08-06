/*
Authors: _xeroxz#7212
Email: xerox@hacks.ltd
Version: 1.3
*/

#pragma once
#include <cstdint>
namespace offsets {

	namespace base_offsets {

		 constexpr uintptr_t game_manager = 0x5225280;
		inline constexpr uintptr_t fov_manager = 0x5225270;
		inline constexpr uintptr_t status_manager = 0x5225220;
		inline constexpr uintptr_t network_manager = 0x52124c0;
		inline constexpr uintptr_t round_manager = 0x52124b8;
		inline constexpr uintptr_t glow_manager = 0x5e99be0;
		inline constexpr uintptr_t skin_manager = 0x5e9a290;
		inline constexpr uintptr_t camrea_manager = 0x5225108;
		inline constexpr uintptr_t game_profile = 0x5212338;
		inline constexpr uintptr_t spoof_manager = 0x5212418;
		inline constexpr uintptr_t v_table = 0x37ec998;
		inline constexpr uintptr_t settings_manager = 0x5e97fb0;

	}
	namespace d3d11 {

		//broken
		//inline constexpr uintptr_t d3d11_swap_table = 0xffff8004eecf0000;

	}
	namespace settings {

		//this needs to be set before game/round starts 
		inline constexpr uintptr_t fov_setting = 0x458;

	}

	namespace bones
	{
		inline constexpr uintptr_t head = 0x670;
		inline constexpr uintptr_t feet = 0x6C0;

	}

	namespace speed {

		// another sig of it just in case 48 8B 48 ? 48 85 C9 74 21 E8 ? ? ? ? 48 
		inline constexpr uintptr_t speed_chain_1 = 0x30;
		inline constexpr uintptr_t speed_chain_2 = 0x30;
		// 48 89 43 ? 48 8D 05 ? ? ? ? 48 89 43 ? 48 8B 43 ? 48 85 C0 74 0B 48 8D 4B ? 45 <-- another signature just in case 
		inline constexpr uintptr_t speed_chain_3 = 0x38;
		// F3 0F 59 43 ? 48 8B 5C 24 ? F3 <--- another signature just in case 
		inline constexpr uintptr_t speed_chain_4 = 0x0;

	}
	namespace glow_offsets {

		inline constexpr uintptr_t glow_base = 0xb8;
		inline constexpr uintptr_t glow_red = 0x110;
		inline constexpr uintptr_t glow_green = 0x114;
		inline constexpr uintptr_t glow_blue = 0x118;
		inline constexpr uintptr_t glow_alpha = 0x138;
		inline constexpr uintptr_t glow_distance = 0x130;
		inline constexpr uintptr_t glow_opacity = 0x13c;

	}
	namespace camrea_offsets {

		//read as vector3<float>() 
		//just in case this sig breaks 48 8B 47 ? 48 85 C0 74 26 48 8B 40 ? 48 
		inline constexpr uintptr_t view_angles_chain1 = 0x20;
		inline constexpr uintptr_t view_angles_chain2 = 0x1170;
		inline constexpr uintptr_t view_angles_chain3 = 0xc0;


		inline constexpr uintptr_t engine_link = 0xE0;
		inline constexpr uintptr_t engine = 0x1D8;
		inline constexpr uintptr_t camera = 0x8;

		inline constexpr uintptr_t fov_x = 0x110;
		inline constexpr uintptr_t fov_y = 0x124;
		inline constexpr uintptr_t forward = 0xF0;
		inline constexpr uintptr_t up = 0xE0;
		inline constexpr uintptr_t right = 0xD0;
		inline constexpr uintptr_t translation = 0x100;

	}
	namespace entity {

		inline constexpr uintptr_t entity_container_chain1 = 0x68;
		static constexpr uint8_t entity_container_chain2 = 0x0; //deref 
		inline constexpr uintptr_t entity_container_chain3 = 0x28;
		namespace entity_spotted {

			inline constexpr uintptr_t spotted_chain = 0xd8;
			inline constexpr uintptr_t entity_component_list_begin = 0x80;
			//0xf0 - 0x80 = 0x70 / 0x8 = E (14 times we loop over components) 
			inline constexpr uintptr_t entity_component_list_end = 0xf0;
			inline constexpr uintptr_t enable_spotted_1 = 0x532;
			inline constexpr uintptr_t enable_spotted_2 = 0x534;
			inline constexpr uintptr_t enable_spotted_icon = 0x1133808;
			inline constexpr uintptr_t enable_spotted_name = 0x1133924;

		}
		inline constexpr uintptr_t entity_list = 0x1c8;
		//Read<DWORD>(gameManager + OFFSET_GAME_MANAGER_ENTITY_COUNT) & 0x3fffffff; 
		inline constexpr uintptr_t entity_count = 0x1d0;
		inline constexpr uintptr_t entity_object = 0x8;
		inline constexpr uintptr_t entity_pawn = 0x20;

		inline constexpr uintptr_t health1 = 0x28; 
		inline constexpr uintptr_t health2 = 0xD8;
		inline constexpr uintptr_t health3 = 0x8;
		inline constexpr uintptr_t health4 = 0x148;

		inline constexpr uintptr_t team_1 = 0xA8;
		inline constexpr uintptr_t team = 0x19E;


	}
	namespace gun_mod {

		inline constexpr uintptr_t no_recoil = 0x3961024;
		inline constexpr uintptr_t damage_mod_chain1 = 0x1f8;
		inline constexpr uintptr_t damage_mod_chain2 = 0xD8;
		inline constexpr uintptr_t damage_mod_chain3 = 0x48;
		inline constexpr uintptr_t damage_mod_chain4 = 0x130;
		inline constexpr uintptr_t damage_mod_chain5 = 0x130;
		inline constexpr uintptr_t damage_mod_chain6 = 0x0;
		inline constexpr uintptr_t damage_mod_chain7 = 0x40;

	}
	inline constexpr uintptr_t unlock_all = 0x134b7f5;

}
