#pragma once
#include <atomic>
#include <cstdint>
#include <vector>

#include "memory.h"
#include "offsets.h"
#include "vec3_t.hpp"

namespace player {

	struct player_struct
	{
		uintptr_t entity;
		uintptr_t player_pawn;
		char* name;
		int team;
		int health;

		vec3_t head;
		vec3_t feet;
	};

	class player_list
	{
	public:
		player_list();
		void update_list();
		std::vector<player_struct> players{};
		player_struct local_player{};

	private:

		void update_local_player();

		mem::memory mem{};
		uintptr_t game_manager{};
		uintptr_t profile_manager{};
		uintptr_t entity_list{};

	};


	namespace player_mod
	{

		inline std::atomic<bool> glow_enabled{};

		typedef struct _color
		{
			float red;
			float blue;
			float green;
		} color;

		typedef struct _color_info
		{
			float distance;
			float alpha;
			float opacity;
		} color_info;

		inline float lred{ -1 },
			lblue{ -1 },
			lgreen{ -1 },
			ldistance{ -1 },
			lalpha{ -1 },
			lopacity{ -1 };

		class glow_effects {

		public:

			void input_handler(bool toggle,
				float red,
				float blue,
				float green,
				float distance,
				float alpha,
				float opacity
			);

		private:

			color default_color = { 0.5372549, 0.5372549, 0.5372549 };
			color_info default_color_data = { 5, 4, 0.5 };

			void enable(float red,
				float blue,
				float green,
				float distance,
				float alpha,
				float opacity
			);
			void disable();
		};
	}
}