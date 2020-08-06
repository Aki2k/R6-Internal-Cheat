#include <iostream>

#include "hook.hpp"
#include "math.hpp"
#include "memory.h"
#include "offsets.h"
#include "esp.h"
#include "common.hpp"
#include "vec3_t.hpp"

namespace esp
{

	void draw_esp::box_esp()
	{
		//get all players
		player_list.update_list();

		for (auto player : player_list.players)
		{

			//w2s head
			player.head = cam.w2s(
				mem::read<vec3_t>(
					player.player_pawn + offsets::bones::head
					)
			);

			//w2s head
			player.feet = cam.w2s(
				mem::read<vec3_t>(
					player.player_pawn + offsets::bones::feet
					)
			);


			if (player.head.x < 0 || player.head.x > ImGui::GetIO().DisplaySize.x || player.head.y < 0 || player.head.y > ImGui::GetIO().DisplaySize.y || player.head.z < 0) continue;
			if (player.feet.x < 0 || player.feet.x > ImGui::GetIO().DisplaySize.x || player.feet.y < 0 || player.head.y > ImGui::GetIO().DisplaySize.y || player.feet.z < 0) continue;

			float h = (player.feet.y - player.head.y);
			float h2 = abs(player.feet.x - player.head.x);
			h = (h > h2) ? h : h2;
			float w = h / 1.5;
			float l = h / 4.0;
			float corr = h / 10;

			float H1 = player.feet.x - (w / 2);
			float H2 = player.feet.x + (w / 2);
			float B1 = player.feet.x - (w / 2);
			float B2 = player.feet.x + (w / 2);

			if (player.team != player_list.local_player.team)
			{
				hook::renderer.draw_line(red, { H1, player.head.y - corr }, { H1, player.head.y + l - corr }, 2.0); //1
				hook::renderer.draw_line(red, { H1, player.head.y - corr }, { H1 + l, player.head.y - corr }, 2.0); //2
				hook::renderer.draw_line(red, { H2, player.head.y - corr }, { H2 - l, player.head.y - corr }, 2.0); //3
				hook::renderer.draw_line(red, { H2, player.head.y - corr }, { H2, player.head.y + l - corr }, 2.0); //4
				hook::renderer.draw_line(red, { B2, player.feet.y }, { B2, player.feet.y - l }, 2.0); //5
				hook::renderer.draw_line(red, { B2, player.feet.y }, { B2 - l, player.feet.y }, 2.0); //6
				hook::renderer.draw_line(red, { B1, player.feet.y }, { B1, player.feet.y - l }, 2.0); //7
				hook::renderer.draw_line(red, { B1, player.feet.y }, { B1 + l, player.feet.y }, 2.0); //8
			}
			else
			{
				hook::renderer.draw_line(blue, { H1, player.head.y - corr }, { H1, player.head.y + l - corr }, 2.0); //1
				hook::renderer.draw_line(blue, { H1, player.head.y - corr }, { H1 + l, player.head.y - corr }, 2.0); //2
				hook::renderer.draw_line(blue, { H2, player.head.y - corr }, { H2 - l, player.head.y - corr }, 2.0); //3
				hook::renderer.draw_line(blue, { H2, player.head.y - corr }, { H2, player.head.y + l - corr }, 2.0); //4
				hook::renderer.draw_line(blue, { B2, player.feet.y }, { B2, player.feet.y - l }, 2.0); //5
				hook::renderer.draw_line(blue, { B2, player.feet.y }, { B2 - l, player.feet.y }, 2.0); //6
				hook::renderer.draw_line(blue, { B1, player.feet.y }, { B1, player.feet.y - l }, 2.0); //7
				hook::renderer.draw_line(blue, { B1, player.feet.y }, { B1 + l, player.feet.y }, 2.0); //8
			}
		}
	}

	void draw_esp::health_bar()
	{
		//get all players
		player_list.update_list();

		for (auto player : player_list.players)
		{

			//w2s head
			player.head = cam.w2s(
				mem::read<vec3_t>(
					player.player_pawn + offsets::bones::head
				)
			);

			//w2s head
			player.feet = cam.w2s(
				mem::read<vec3_t>(
					player.player_pawn + offsets::bones::feet
				)
			);

			if (player.head.x < 0 || player.head.x > ImGui::GetIO().DisplaySize.x || player.head.y < 0 || player.head.y > ImGui::GetIO().DisplaySize.y || player.head.z < 0) continue;
			if (player.feet.x < 0 || player.feet.x > ImGui::GetIO().DisplaySize.x || player.feet.y < 0 || player.head.y > ImGui::GetIO().DisplaySize.y || player.feet.z < 0) continue;

			float h = (player.feet.y - player.head.y);
			float h2 = abs(player.feet.x - player.head.x);
			h = (h > h2) ? h : h2;
			float w = h / 2.5;
			float l = h / 4.0;
			float corr = h / 10;

			float blackpx = w / 16;
			hook::renderer.draw_line(black,ImVec2(player.feet.x - (w / 2) - (l / 2), player.feet.y), ImVec2(player.feet.x - (w / 2) - (l / 2), player.feet.y - h - corr), blackpx);
			hook::renderer.draw_line(green, ImVec2(player.feet.x - (w / 2) - (l / 2), player.feet.y), ImVec2(player.feet.x - (w / 2) - (l / 2), player.feet.y - ((h + corr) * (player.health / 120.0))), blackpx / 1.3);
			float cas = (h + corr) / 4.0;
			hook::renderer.draw_line(black, ImVec2(player.feet.x - (w / 2) - (blackpx / 2) - (l / 2), player.feet.y - cas), ImVec2(player.feet.x - (w / 2) + (blackpx / 2) - (l / 2), player.feet.y - cas), 1.0);
			hook::renderer.draw_line(black, ImVec2(player.feet.x - (w / 2) - (blackpx / 2) - (l / 2), player.feet.y - 2 * cas), ImVec2(player.feet.x - (w / 2) + (blackpx / 2) - (l / 2), player.feet.y - 2 * cas), 1.0);
			hook::renderer.draw_line(black, ImVec2(player.feet.x - (w / 2) - (blackpx / 2) - (l / 2), player.feet.y - 3 * cas), ImVec2(player.feet.x - (w / 2) + (blackpx / 2) - (l / 2), player.feet.y - 3 * cas), 1.0);
		}
	}

	void draw_esp::display_distance()
	{


	}
}