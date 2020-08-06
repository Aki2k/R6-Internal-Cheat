#include "unlock_all.h"
#include "offsets.h"
#include "common.hpp"


namespace unlock_all {

	unlock_all::unlock_all()
	{}

	void unlock_all::enable()
	{
		if (unlock_all_enabled)
			return;

		//if we havent patched terminate process then do so
		if (!common::patched_term_proc)
			if (!common::patch_terminate_process())
				return;

		unlock_all_enabled = true;
		mem::memory mem;

		mem::write_to_readonly(
			mem.get_base_addr() + offsets::unlock_all,
			unlock_all_enable_bytes,
			sizeof(unlock_all_enable_bytes)
		);
	}

	void unlock_all::disable()
	{

		if (!unlock_all_enabled)
			return;

		//if we havent patched terminate process then do so
		if (!common::patched_term_proc)
			if (!common::patch_terminate_process())
				return;

		unlock_all_enabled = false;
		mem::memory mem;

		mem::write_to_readonly(
			mem.get_base_addr() + offsets::unlock_all,
			unlock_all_disable_bytes,
			sizeof(unlock_all_disable_bytes)
		);
	}

	void unlock_all::input_interface(bool toggle)
	{
		toggle ? enable() : disable();
	}
}