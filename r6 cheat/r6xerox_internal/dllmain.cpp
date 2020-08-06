#include <iostream>
#include <thread>
#include <memory>
#include <windows.h>

#include "hook.hpp"
#include "input_handler.hpp"

using namespace std;

//--- our main function
void run() {

	hook::setup_present_hook();
	input_handler::init();
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		// create a thread and leave.
		std::thread(&run).detach();
		break;
    case DLL_THREAD_ATTACH:
		break;
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}