#include "render.hpp"
#include "display_handler.hpp"
#include "input_handler.hpp"


using namespace input_handler::elements;

namespace rendering
{

	renderer::renderer()
		: _device_context(0), _render_target_view(0)
	{}

	renderer::renderer(IDXGISwapChain* swapchain)
	{
		auto device = get_device(swapchain);
		_device_context = get_device_context(device);
		_render_target_view = get_render_target_view(swapchain, device);
		

		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		ImGui::GetIO().IniFilename = 0;

		HWND r6handle = FindWindow(nullptr, "Rainbow Six");

		ImGui_ImplWin32_Init(r6handle); // change this to get current window
		ImGui_ImplDX11_Init(device, _device_context);
		imgui_style_init();
	}

	void renderer::imgui_style_init()
	{

		ImGuiStyle& st = ImGui::GetStyle();
		st.FrameBorderSize = 1.0f;
		st.FramePadding = ImVec2(4.0f, 2.0f);
		st.ItemSpacing = ImVec2(8.0f, 2.0f);
		st.WindowBorderSize = 1.0f;
		st.TabBorderSize = 1.0f;
		st.WindowRounding = 1.0f;
		st.ChildRounding = 1.0f;
		st.FrameRounding = 1.0f;
		st.ScrollbarRounding = 1.0f;
		st.GrabRounding = 1.0f;
		st.TabRounding = 1.0f;

		// Setup style
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 0.95f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.53f, 0.53f, 0.53f, 0.46f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.85f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.22f, 0.22f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 0.53f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.48f, 0.47f, 0.47f, 0.91f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.55f, 0.55f, 0.62f);
		colors[ImGuiCol_Button] = ImVec4(0.50f, 0.50f, 0.50f, 0.63f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.67f, 0.68f, 0.63f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.26f, 0.26f, 0.26f, 0.63f);
		colors[ImGuiCol_Header] = ImVec4(0.54f, 0.54f, 0.54f, 0.58f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.64f, 0.65f, 0.65f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.25f, 0.80f);
		colors[ImGuiCol_Separator] = ImVec4(0.58f, 0.58f, 0.58f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.64f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.81f, 0.81f, 0.81f, 0.64f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.87f, 0.87f, 0.87f, 0.53f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.87f, 0.87f, 0.87f, 0.74f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.87f, 0.87f, 0.87f, 0.74f);
		colors[ImGuiCol_Tab] = ImVec4(0.01f, 0.01f, 0.01f, 0.86f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.68f, 0.68f, 0.68f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.77f, 0.33f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.87f, 0.55f, 0.08f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.47f, 0.60f, 0.76f, 0.47f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.58f, 0.58f, 0.58f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

	}

	void renderer::release() const
	{
		if (_device_context)
			_device_context->Release();
		if (_render_target_view)
			_render_target_view->Release();
	}

	void renderer::begin() const
	{
		
		_device_context->OMSetRenderTargets(1, &_render_target_view, nullptr);
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void renderer::end() const
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void renderer::begin_overlay() const
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
		ImGui::SetNextWindowCollapsed(false, ImGuiCond_Always);
		ImGui::Begin("##overlay", reinterpret_cast<bool*>(false), ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs); //start closed
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Always);
		
	}

	void renderer::end_overlay() const
	{

		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->PushClipRectFullScreen();
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);
	}

	void renderer::draw_menu() const
	{
		
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.85f });
		ImGui::SetNextWindowSize({ 300.f, 500.f }, ImGuiCond_Always);
		ImGui::SetNextWindowCollapsed(false, ImGuiCond_Always);
		ImGui::Begin("[~] Go Stupid", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoResize); // start open
		ImGui::SetWindowPos(ImVec2(0, 25), ImGuiCond_FirstUseEver);

		{ // beginning of ESP section
			ImGui::Dummy(ImVec2(0, 10));
			ImGui::Text("ESP");
			ImGui::Separator();
			{
				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
				ImGui::Checkbox(element_name::spotted_button, reinterpret_cast<bool*>(&toggle::spotted_esp_button));
				ImGui::SameLine();
				ImGui::Text("spotted esp");

				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
				ImGui::Checkbox(element_name::esp_corners, reinterpret_cast<bool*>(&toggle::esp_corners));
				ImGui::SameLine();
				ImGui::Text("box esp");
				
				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
				ImGui::Checkbox(element_name::esp_health_bar, reinterpret_cast<bool*>(&toggle::esp_health_bar));
				ImGui::SameLine();
				ImGui::Text("health bar");
			}
		}
		
		{ // beginning of PLAYER MOD section
			ImGui::Dummy(ImVec2(0, 20));
			ImGui::Text("PLAYER MOD");
			ImGui::Separator();
			{
				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
				ImGui::Checkbox(element_name::glow_button, reinterpret_cast<bool*>(&toggle::glow_button));
				ImGui::SameLine();
				ImGui::Text("enable glow");
				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
				ImGui::SliderFloat(element_name::glow_red, reinterpret_cast<float*>(&slider::glow_red), 0.0f, 500.0f);
				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
				ImGui::SliderFloat(element_name::glow_blue, reinterpret_cast<float*>(&slider::glow_blue), 0.0f, 500.0f);
				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
				ImGui::SliderFloat(element_name::glow_green, reinterpret_cast<float*>(&slider::glow_green), 0.0f, 500.0f);
				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
				ImGui::SliderFloat(element_name::glow_distance, reinterpret_cast<float*>(&slider::glow_distance), 0.0f, 10.0f);
				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
				ImGui::SliderFloat(element_name::glow_alpha, reinterpret_cast<float*>(&slider::glow_alpha), 0.0f, 10.0f);
				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
				ImGui::SliderFloat(element_name::glow_opacity, reinterpret_cast<float*>(&slider::glow_opacity), 0.0f, 10.0f);
				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
			}
		}

		{// beginning of GUN MOD section
			ImGui::Dummy(ImVec2(0, 20));
			ImGui::Text("GUN MOD");
			ImGui::Separator();
			{
				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
				ImGui::Checkbox(element_name::no_recoil_button, reinterpret_cast<bool*>(&toggle::no_recoil_button));
				ImGui::SameLine();
				ImGui::Text("recoil mod");
				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
				ImGui::SliderFloat(element_name::no_recoil, reinterpret_cast<float*>(&slider::no_recoil), 0.0f, 5.0f);
			}
		}

		{ //beginning of ETC section
			ImGui::Dummy(ImVec2({ 0, 20 }));
			ImGui::Text("ETC");
			ImGui::Separator();
			{
				ImGui::Dummy(ImVec2(10, 0));
				ImGui::SameLine();
				ImGui::Checkbox(element_name::unlock_all_button, reinterpret_cast<bool*>(&toggle::unlock_all_button));
				ImGui::SameLine();
				ImGui::Text("unlock all");
			}
		}
	}

	ID3D11Device* renderer::get_device(IDXGISwapChain* swapchain) const
	{
		ID3D11Device* device;
		swapchain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device));
		return device;
	}

	ID3D11DeviceContext* renderer::get_device_context(ID3D11Device* device) const
	{
		ID3D11DeviceContext* context;
		device->GetImmediateContext(&context);
		return context;
	}

	ID3D11RenderTargetView* renderer::get_render_target_view(IDXGISwapChain* swapchain, ID3D11Device* device) const
	{
		ID3D11Texture2D* backbuffer = NULL;
		swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backbuffer));
		ID3D11RenderTargetView* render_target_view = NULL;
		device->CreateRenderTargetView(backbuffer, NULL, &render_target_view);
		backbuffer->Release();
		return render_target_view;
	}

	void renderer::draw_text(const ImVec2& pos, std::string_view text, const ImVec4& colour, bool shadow)
	{
		if (shadow)
		{
			constexpr auto offset = 1.f;
			const auto colour = ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f });

			ImGui::GetCurrentWindow()->DrawList->AddText({ pos.x - offset, pos.y - offset }, colour, text.data());
			ImGui::GetCurrentWindow()->DrawList->AddText({ pos.x - offset, pos.y + offset }, colour, text.data());
			ImGui::GetCurrentWindow()->DrawList->AddText({ pos.x - offset, pos.y }, colour, text.data());

			ImGui::GetCurrentWindow()->DrawList->AddText({ pos.x, pos.y + offset }, colour, text.data());
			ImGui::GetCurrentWindow()->DrawList->AddText({ pos.x, pos.y - offset }, colour, text.data());

			ImGui::GetCurrentWindow()->DrawList->AddText({ pos.x + offset, pos.y - offset }, colour, text.data());
			ImGui::GetCurrentWindow()->DrawList->AddText({ pos.x + offset, pos.y + offset }, colour, text.data());
			ImGui::GetCurrentWindow()->DrawList->AddText({ pos.x + offset, pos.y }, colour, text.data());
		}

		ImGui::GetCurrentWindow()->DrawList->AddText(pos, ImGui::GetColorU32(colour), text.data());
	}

	void renderer::draw_box(const ImVec2& pos, const ImVec2& dimensions, const ImVec4& colour, float thickness, float rounding) const
	{
		if (true /* shadow */)
		{
			const auto black = ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f });
			ImGui::GetCurrentWindow()->DrawList->AddRect(pos, { pos.x + dimensions.x, pos.y + dimensions.y }, black, rounding, 0, thickness + 1);
		}

		ImGui::GetCurrentWindow()->DrawList->AddRect(pos, { pos.x + dimensions.x, pos.y + dimensions.y }, ImGui::GetColorU32(colour), rounding, 0, thickness);
	}

	void renderer::draw_filled_box(const ImVec2& pos, const ImVec2& dimensions, const ImVec4& colour, float rounding) const
	{
		ImGui::GetCurrentWindow()->DrawList->AddRectFilled(pos, { pos.x + dimensions.x, pos.y + dimensions.y }, ImGui::GetColorU32(colour), rounding, 0);
	}

	void renderer::draw_line(ImVec4 color, ImVec2 from, ImVec2 to, float thickness)
	{
		ImGui::GetCurrentWindow()->DrawList->AddLine(from, to, ImGui::GetColorU32(color), thickness);
	}
}