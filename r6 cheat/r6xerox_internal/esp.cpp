#include "offsets.h"
#include "memory.h"
#include "common.hpp"
#include "esp.h"

using namespace esp;
using namespace offsets::entity;

spotted::spotted()
{}

//--- definition of enable spotted
void spotted::enable()
{

	//if spotted alread enabled
	if (currently_spotting)
		return;

	currently_spotting = true;
	mem::memory mem;

	//if we havent patched terminate process then do so
	if (!common::patched_term_proc)
		if (!common::patch_terminate_process())
			return;

	//enable icon spotted esp
	mem::write_to_readonly(
		mem.get_base_addr() + (entity_spotted::enable_spotted_icon + 0x12), //0x9 only for enemy 
		spotted_enable_icon_bytes,
		sizeof(spotted_enable_icon_bytes)
	);

	//enable name spotted esp
	mem::write_to_readonly(
		mem.get_base_addr() + (entity_spotted::enable_spotted_name + 0x12), //0x9 only for enemy 
		spotted_enable_name_bytes,
		sizeof(spotted_enable_name_bytes)
	);

}

//--- definition of disable spotted
void spotted::disable()
{

	//if its already disabled
	if (!currently_spotting)
		return;

	currently_spotting = false;
	mem::memory mem;

	//dont know how this could happen but just in case
	if (!common::patched_term_proc)
		common::patch_terminate_process();

	//write 00 to icon
	mem::write_to_readonly(
		mem.get_base_addr() + (entity_spotted::enable_spotted_icon + 0x12), //0x9 only for enemy 
		spotted_disable_icon_bytes,
		sizeof(spotted_disable_icon_bytes)
	);

	//write 00 to spotted name
	mem::write_to_readonly(
		mem.get_base_addr() + (entity_spotted::enable_spotted_name + 0x12), //0x9 only for enemy 
		spotted_disable_name_bytes,
		sizeof(spotted_disable_name_bytes)
	);
}

void spotted::input_interface(bool toggle)
{
	toggle ? enable() : disable();
}
