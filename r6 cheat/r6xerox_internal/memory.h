#pragma once
#include <windows.h>
#include <cstdint>
#include <TlHelp32.h>
#include <vector>
#include <iostream>

namespace mem {

	//--- definition of write_to_readonly
	__forceinline bool write_to_readonly(std::uintptr_t write_to, const std::uint8_t bytes_to_write[], std::size_t size_to_write)
	{
		DWORD old_protect{};
		if (VirtualProtect((LPVOID)write_to, size_to_write, PAGE_READWRITE, &old_protect) == NULL) return false;
		memcpy((LPVOID)write_to, bytes_to_write, size_to_write);
		if (VirtualProtect((LPVOID)write_to, size_to_write, old_protect, &old_protect) == NULL) return false;
		return true;
	}


	//--- definition of read
	template<class T>
	__forceinline T read(uintptr_t address) {

		return *(T*)address;

	}

	//--- definition of write
	template<class S>
	__forceinline void write(uintptr_t address, S value) {

		*(uintptr_t*)address = value;

	}

	//--- definition of read_chain
	__forceinline uintptr_t read_chain(std::vector<uintptr_t> chain) {

		uintptr_t chain_result = chain[0];

		for (auto idx = 1u; idx < chain.size(); ++idx)
		{
			chain_result = read<uintptr_t>(chain_result + chain[idx]);
		}

		return chain_result;
	}

	class memory {

	public:

		memory();
		memory(const char* module_name);
		uintptr_t get_module_baseaddr(DWORD procId, const char* modName);
		uintptr_t get_base_addr();
		DWORD get_pid();

	private:
		DWORD pid;
		uintptr_t baseAddress;

	};

	inline memory memory_handler{};
}