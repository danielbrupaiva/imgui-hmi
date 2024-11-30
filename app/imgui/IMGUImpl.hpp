#pragma once

#include <memory>
#include "spec.hpp"
#include "glfw.hpp"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "font.hpp"
#include "IMGUI.hpp"
#include "widgets_impl.hpp"

namespace App
{
class IMGUImpl: public IMGUI
{
public:
	~IMGUImpl() override
	{
		IMGUImpl::shutdown();
	};
	explicit IMGUImpl(Spec &spec)
		: m_spec{spec}, m_api{std::make_unique<GLFW>(spec)}
	{
		m_is_init = IMGUImpl::init();
		IM_ASSERT(m_is_init);
	};
	// Prevent copying
	IMGUImpl(const IMGUImpl &) = delete;
	IMGUImpl &operator=(const IMGUImpl &) = delete;
	// Render method
	void render(const std::function<void()> &render) override;

	/*Getter and Setters*/
	[[nodiscard]] inline bool is_close() const
	{
		return m_api->is_close();
	}

	inline void close() const
	{
		m_api->close();
	}

	[[nodiscard]] inline const Spec &get_spec() const
	{
		return m_spec;
	}

	[[nodiscard]] inline bool is_init() const
	{
		return m_is_init;
	}

	[[nodiscard]] inline Widget::Wrapper &widgets() override
	{
		return m_widgets;
	}

	[[nodiscard]] inline ILayout &layout() override
	{
		return m_layout;
	}

private:
	bool init() override
	{
		if (!m_api) {
			throw std::runtime_error("No API avaiable! Could not initialize IMGUI");;
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO &io = ImGui::GetIO();
		(void) io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		set_style();

		Font::init(io);

		IMGUImpl::setup_backend();

		IM_ASSERT(get_imgui_context());

		return true;
	};

	void shutdown() override
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		m_is_init = false;
	};
	//TODO: Create a project style color
	static void set_style()
	{
		ImGuiStyle *style = &ImGui::GetStyle();
		/* Rounding */
		style->WindowRounding = 6.0f;
		style->FrameRounding = 6.0f;
		style->ChildRounding = 6.0f;
		style->PopupRounding = 6.0f;
		style->ScrollbarRounding = 6.0f;
		style->GrabRounding = 6.0f;
		/* Scrollbar and Grab*/
		style->ScrollbarSize = 20.0f;
		style->GrabMinSize = 20.0f;
		/* Padding and Spacing*/
		style->WindowPadding = ImVec2(4.0f, 4.0f);
		style->FramePadding = ImVec2(4.0f, 4.0f);
		style->ItemSpacing = ImVec2(4.0f, 4.0f);
		style->ItemInnerSpacing = ImVec2(4.0f, 4.0f);
		style->IndentSpacing = 0.0f;

		ImVec4 *colors = style->Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.109f, 0.109f, 0.109f, 0.94f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.109f, 0.109f, 0.109f, 0.94f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.109f, 0.109f, 0.109f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.173f, 0.173f, 0.173f, 1.0f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.271f, 0.271f, 0.271f, 1.0f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.271f, 0.271f, 0.271f, 1.0f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.173f, 0.173f, 0.173f, 1.0f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.173f, 0.173f, 0.173f, 1.0f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.173f, 0.173f, 0.173f, 1.0f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.271f, 0.271f, 0.271f, 1.0f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.173f, 0.173f, 0.173f, 1.0f);
		colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
		colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
		colors[ImGuiCol_TabSelected] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
		colors[ImGuiCol_TabSelectedOverline] = colors[ImGuiCol_HeaderActive];
		colors[ImGuiCol_TabDimmed] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
		colors[ImGuiCol_TabDimmedSelected] = ImLerp(colors[ImGuiCol_TabSelected], colors[ImGuiCol_TitleBg], 0.40f);
		colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f); // Prefer using Alpha=1.0 here
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f); // Prefer using Alpha=1.0 here
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	};

	bool setup_backend() override
	{
		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(get_glfw_window_from_api(), true);
		ImGui_ImplOpenGL3_Init(m_spec.shader_version.c_str());
		return true;
	};

	[[nodiscard]] inline GLFWwindow *get_glfw_window_from_api() const
	{
		return m_api->get_window();
	}

	[[nodiscard]] static ImGuiContext *get_imgui_context()
	{
		ImGuiContext *context = ImGui::GetCurrentContext();
		if (context == nullptr) {
			std::string msg = "No current imgui context";
			logger.error("{}", msg);
			throw std::runtime_error(msg);
		}
		return context;
	}

private:
	Spec					m_spec;
	std::unique_ptr<GLFW>	m_api;
	Widget::Wrapper			m_widgets;
	Layout					m_layout;

	bool					m_is_init = false;
	bool					m_entire_viewport = true;
	std::unique_ptr<bool>	m_open = nullptr;
	ImVec2					m_position = ImVec2(0, 0);
	ImGuiWindowFlags		m_flags = ImGuiWindowFlags_NoDecoration
									| ImGuiWindowFlags_NoCollapse
									| ImGuiWindowFlags_NoMove
									| ImGuiWindowFlags_NoBringToFrontOnFocus;
							//		| ImGuiWindowFlags_NoBackground;
};

inline void IMGUImpl::render(const std::function<void()> &render)
{
	glfwPollEvents();
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//TODO: Create auto ajusted windows strategy
	//    const ImGuiViewport *viewport = ImGui::GetMainViewport();
	//    ImGui::SetNextWindowPos(m_entire_viewport ? viewport->WorkPos : viewport->Pos);
	//    ImGui::SetNextWindowSize(m_entire_viewport ? viewport->WorkSize : viewport->Size);
	// Hardcoded position and window size
	ImGui::SetNextWindowPos(m_position);
	ImGui::SetNextWindowSize(m_spec.window_size, ImGuiCond_Always);

	if (ImGui::Begin("MAIN", m_open.get(), m_flags)) {
		render();
	}
	ImGui::End();
	// Rendering
	ImGui::Render();
	int32_t display_w, display_h;
	glfwGetFramebufferSize(get_glfw_window_from_api(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(m_spec.bg_color.x * m_spec.bg_color.w,
	             m_spec.bg_color.y * m_spec.bg_color.w,
	             m_spec.bg_color.z * m_spec.bg_color.w,
	             m_spec.bg_color.w);

	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(get_glfw_window_from_api());
};
}
