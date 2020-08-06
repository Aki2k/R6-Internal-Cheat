#pragma once
#include <d3d11.h>

#include "render.hpp"
#include "imgui/imgui_impl_win32.h"
#include "display_handler.hpp"
#include "input_handler.hpp"
#include "memory.h"

namespace hook {

	inline rendering::renderer renderer{};
	inline WNDPROC windowProc;
	inline HWND windowHandle;
	inline uintptr_t original_present{};
	inline uintptr_t original_buffer_resize{};

	__forceinline HRESULT __stdcall hooked_present(IDXGISwapChain* _swap_chain, UINT _sync_interval, UINT _flags)
	{
		if (static std::atomic<bool> ran = false; !ran.exchange(true))
		{
			renderer.release();
			renderer = rendering::renderer(_swap_chain);
			display::init();
		}

		renderer.begin();
		renderer.begin_overlay();
		renderer.draw_text({ 5, 5 }, "XEROX(TM) KNSA(R) V2.3", { 153, 0, 0 , 1 });
		if (input_handler::elements::toggle::esp_corners)
			input_handler::draw_esp.box_esp();
		if (input_handler::elements::toggle::esp_health_bar)
			input_handler::draw_esp.health_bar();
		renderer.end_overlay();
		if (display::inside_menu)
			renderer.draw_menu();
		renderer.end();
		return reinterpret_cast<std::decay_t<decltype(&hooked_present)>>(original_present)(_swap_chain, _sync_interval, _flags);
	}


	__forceinline HRESULT __stdcall hooked_resize_buffer(IDXGISwapChain* pThis, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
	{
		renderer.release();
		HRESULT result = reinterpret_cast<std::decay_t<decltype(&hooked_resize_buffer)>>(original_buffer_resize)(pThis, BufferCount, Width, Height, NewFormat, SwapChainFlags);
		renderer = rendering::renderer(pThis);
		return result;
	}
	

	//--- changes present to our function
	__forceinline void setup_present_hook() {

		DWORD dwProtect;
		mem::memory mem;
		LPVOID * swap_table = reinterpret_cast<LPVOID *>(mem.get_module_baseaddr(mem.get_pid(), "dxgi.dll") + 0x93E68);

		original_present = reinterpret_cast<uintptr_t>(swap_table[8]);
		original_buffer_resize = reinterpret_cast<uintptr_t>(swap_table[13]);
		VirtualProtect(swap_table, 8, PAGE_READWRITE, &dwProtect);
		//hook present
		swap_table[8] = reinterpret_cast<LPVOID *>(&hooked_present);
		//hook resize buffer
		swap_table[13] = reinterpret_cast<LPVOID*>(&hooked_resize_buffer);
		VirtualProtect(swap_table, 8, dwProtect, NULL);

	}
}