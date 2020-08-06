#include <vector>

#include "player.h"
#include "offsets.h"
#include "memory.h"

using namespace player::player_mod;

void glow_effects::enable(float red,
	float blue,
	float green,
	float distance,
	float alpha,
	float opacity
)
{

	if (lred == red and
		lblue == blue and
		lgreen == green and
		ldistance == distance and
		lalpha == alpha and
		lopacity == opacity
		)
		return;
	mem::memory mem;
	glow_enabled = true;

	lred = red;
	lblue = blue;
	lgreen = green;
	ldistance = distance;
	lalpha = alpha;

	uintptr_t glow_manager = mem::read<uintptr_t>(mem.get_base_addr() + offsets::base_offsets::glow_manager);
	uintptr_t glow_base = mem::read<uintptr_t>(glow_manager + offsets::glow_offsets::glow_base);
	color c = { red, blue, green };
	color_info c_info = { distance, alpha, opacity };
	//write color

	memcpy(reinterpret_cast<void*>(glow_base + offsets::glow_offsets::glow_red), &c, sizeof(c));
	memcpy(reinterpret_cast<void*>(glow_base + offsets::glow_offsets::glow_distance), &c_info, sizeof(c_info));

}

void glow_effects::disable()
{

	if (!glow_enabled)
		return;

	glow_enabled = false;
	mem::memory mem;

	uintptr_t glow_manager = mem::read<uintptr_t>(mem.get_base_addr() + offsets::base_offsets::glow_manager);
	uintptr_t glow_base = mem::read<uintptr_t>(glow_manager + offsets::glow_offsets::glow_base);


	memcpy(reinterpret_cast<void*>(glow_base + offsets::glow_offsets::glow_red), &default_color, sizeof(default_color));
	memcpy(reinterpret_cast<void*>(glow_base + offsets::glow_offsets::glow_distance), &default_color_data, sizeof(default_color_data));
}

void glow_effects::input_handler(bool toggle, 
	float red,
	float green,
	float blue,
	float distance,
	float alpha,
	float opacity
)
{
	toggle ? enable(red,green,blue,distance,alpha, opacity) : disable();
}