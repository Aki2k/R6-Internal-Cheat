#pragma once
#include <Windows.h>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace display
{

	inline WNDPROC oWndProc;
	inline bool inside_menu = false;

	inline LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		if (inside_menu) {
			ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

			return true;
		}
		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
	}

	inline void init()
	{
		oWndProc = (WNDPROC)SetWindowLongPtr(FindWindow(NULL, "Rainbow Six"), -4, (LONG_PTR)WndProc);
	}
}