#pragma once
#include <vector>
#include <atomic>

#include "memory.h"


namespace common {

	inline std::atomic<bool> patched_term_proc = false;

	inline const uint8_t patched_term_proc_shellcode[7] = {
		0xC3, //ret
		0x90, //nop
		0x90, //nop
		0x90, //nop
		0x90, //nop
		0x90, //nop
		0x90  //nop
	};

	inline bool patch_terminate_process()
	{
		mem::memory mem;

		uintptr_t place_to_write = (uintptr_t)GetProcAddress(LoadLibrary("KERNEL32.DLL"), "TerminateProcess");

		if (mem::write_to_readonly(
			place_to_write,
			patched_term_proc_shellcode,
			sizeof(patched_term_proc_shellcode))
			) {
			patched_term_proc = true;
			return true;
		}
		else {
			patched_term_proc = false;
			return false;
		}
	}
}
