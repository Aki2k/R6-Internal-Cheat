#include "memory.h"

using namespace mem;


//--- definition of default constructor
memory::memory()
	: pid(GetCurrentProcessId()), baseAddress(get_module_baseaddr(pid, "RainbowSix.exe"))
{}

//--- definition of constructor
memory::memory(const char* module_name)
	: pid(GetCurrentProcessId()), baseAddress(get_module_baseaddr(pid, module_name))
{}

//--- definition of get_module_baseaddr
uintptr_t memory::get_module_baseaddr(DWORD procId, const char* modName) {
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!strcmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

//--- definition of getpid
DWORD memory::get_pid()
{
	return pid;
}

//--- definition of get_base_addr
uintptr_t memory::get_base_addr() {
	return baseAddress;
}


