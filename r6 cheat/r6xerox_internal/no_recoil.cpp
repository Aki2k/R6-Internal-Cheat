#include "gun_mod.h"
#include "offsets.h"
#include "memory.h"
#include "common.hpp"

using namespace gun_mod;

void no_recoil::enable()
{
	if (no_recoil_enabled)
		return;

	no_recoil_enabled = true;
	mem::memory mem;

	//if we havent patched terminate process then do so
	if (!common::patched_term_proc)
		if (!common::patch_terminate_process())
			return;

	mem::write_to_readonly(
		mem.get_base_addr() + offsets::gun_mod::no_recoil,
		no_recoil_enable,
		sizeof(no_recoil_enable)
	);

}

void no_recoil::disable()
{

	if (!no_recoil_enabled)
		return;

	no_recoil_enabled = false;
	mem::memory mem;

	//if we havent patched terminate process then do so
	if (!common::patched_term_proc)
		if (!common::patch_terminate_process())
			return;

	mem::write_to_readonly(
		mem.get_base_addr() + offsets::gun_mod::no_recoil,
		no_recoil_disable,
		sizeof(no_recoil_disable)
	);
}


void no_recoil::input_interface(bool toggle)
{
	toggle ? enable() : disable();
}