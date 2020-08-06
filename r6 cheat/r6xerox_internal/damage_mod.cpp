#include <vector>

#include "gun_mod.h"
#include "memory.h"
#include "offsets.h"

using namespace gun_mod;
using namespace std;

void damage_mod::input_interface(bool toggle, int bullet_amount)
{
	toggle ? enable(bullet_amount) : disable();
}

void damage_mod::enable(int bullet_amount)
{
	if (lbullet_amount == bullet_amount)
		return;

	damage_mod_enabled = true;
	lbullet_amount = bullet_amount;
	mem::memory mem;

	uintptr_t bullet_amount_offset = mem::read_chain(vector<uintptr_t>{
		mem.get_base_addr(),
			offsets::base_offsets::game_manager,
			offsets::gun_mod::damage_mod_chain1,
			offsets::gun_mod::damage_mod_chain2,
			offsets::gun_mod::damage_mod_chain3,
			offsets::gun_mod::damage_mod_chain4,
			offsets::gun_mod::damage_mod_chain5,
			offsets::gun_mod::damage_mod_chain6
	});

	*(int*)(bullet_amount_offset + offsets::gun_mod::damage_mod_chain7) = bullet_amount;
}

void damage_mod::disable()
{

	if (!damage_mod_enabled)
		return;

	int bullet_normal{ 1 };

	if (!damage_mod_enabled)
		return;

	damage_mod_enabled = false;
	mem::memory mem;

	uintptr_t bullet_amount_offset = mem::read_chain(vector<uintptr_t>{
		mem.get_base_addr(),
		offsets::base_offsets::game_manager,
		offsets::gun_mod::damage_mod_chain1,
		offsets::gun_mod::damage_mod_chain2,
		offsets::gun_mod::damage_mod_chain3,
		offsets::gun_mod::damage_mod_chain4,
		offsets::gun_mod::damage_mod_chain5,
		offsets::gun_mod::damage_mod_chain6
	});

	*(int*)(bullet_amount_offset + offsets::gun_mod::damage_mod_chain7) = bullet_normal;

}