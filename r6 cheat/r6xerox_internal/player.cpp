#include "player.h"

namespace player
{
	player_list::player_list()
	{
		game_manager = mem::read<uintptr_t>(mem.get_base_addr() + offsets::base_offsets::game_manager);
		profile_manager = mem::read<uintptr_t>(mem.get_base_addr() + offsets::base_offsets::game_profile);
		update_list();
	}

	void player_list::update_list()
	{
		players.clear();
		update_local_player();
		entity_list = mem::read<uintptr_t>(game_manager + offsets::entity::entity_list);
		if (entity_list == NULL)
			return;

		DWORD entity_count = (mem::read<DWORD>(game_manager + offsets::entity::entity_count) & 0x3fffffff);

		if (entity_count == NULL)
			return;

		for (auto idx = 1u; idx < entity_count; ++idx)
		{
			player_struct new_player;

			//get entity if you can
			new_player.entity = mem::read<uintptr_t>(entity_list + (0x8 * idx));
			if (new_player.entity == NULL)
				continue;

			//skip player if its yourself
			if (new_player.entity == local_player.entity)
				continue;

			//get player pawn if you can
			new_player.player_pawn = mem::read<uintptr_t>(
				new_player.entity + offsets::entity::entity_pawn
			);

			if (new_player.player_pawn == NULL)
				continue;

			//get team if you can
			uintptr_t team_1 = mem::read<uintptr_t>(new_player.entity + offsets::entity::team_1);
			if (team_1 != NULL)
				new_player.team = mem::read<int>(team_1 + offsets::entity::team);
			else
				new_player.team = 0;

			//get health if you can
			uintptr_t health1 = mem::read<uintptr_t>(new_player.entity + offsets::entity::health1);
			if (health1 != NULL) {
				uintptr_t health2 = mem::read<uintptr_t>(health1 + offsets::entity::health2);
				if (health2 != NULL) {
					uintptr_t health3 = mem::read<uintptr_t>(health2 + offsets::entity::health3);
					new_player.health = mem::read<int>(health3 + offsets::entity::health4);
				}
			}

			players.push_back(new_player);
		}
	}

	void player_list::update_local_player()
	{

		uintptr_t container_1 = mem::read<uintptr_t>(profile_manager + offsets::entity::entity_container_chain1);
		if (container_1 == NULL)
			return;
		uintptr_t container_2 = mem::read<uintptr_t>(container_1 + offsets::entity::entity_container_chain2);
		if (container_2 == NULL)
			return;
		local_player.entity = mem::read<uintptr_t>(container_2 + offsets::entity::entity_container_chain3);
		if (local_player.entity == NULL)
			return;

		uintptr_t team_1 = mem::read<uintptr_t>(local_player.entity + offsets::entity::team_1);
		if (team_1 == NULL)
			return;

		local_player.team = mem::read<int>(team_1 + offsets::entity::team);
	}
}