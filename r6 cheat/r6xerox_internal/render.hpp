#pragma once
#include <iostream>
#include <atomic>
#include <d3d11.h>
#include <string_view>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#pragma comment(lib, "d3d11.lib")

namespace rendering
{

	class renderer
	{
	public:
		renderer();
		explicit renderer(IDXGISwapChain* swapchain);
		void release() const;
		void begin() const;
		void end() const;
		void begin_overlay() const;
		void end_overlay() const;
		void draw_menu() const;
		void draw_text(const ImVec2& pos, std::string_view text, const ImVec4& colour, bool shadow = true);
		void draw_box(const ImVec2& pos, const ImVec2& dimensions, const ImVec4& colour, float thickness = 1.5f, float rounding = 3.f) const;
		void draw_filled_box(const ImVec2& pos, const ImVec2& dimensions, const ImVec4& colour, float rounding = 3.f) const;
		void draw_line(ImVec4 color, ImVec2 from, ImVec2 to, float thickness);
	private:
		void imgui_style_init();
		ID3D11Device* get_device(IDXGISwapChain* swapchain) const;
		ID3D11DeviceContext* get_device_context(ID3D11Device* device) const;
		ID3D11RenderTargetView* get_render_target_view(IDXGISwapChain* swapchain, ID3D11Device* device) const;
		ID3D11DeviceContext* _device_context;
		ID3D11RenderTargetView* _render_target_view;

	};

}