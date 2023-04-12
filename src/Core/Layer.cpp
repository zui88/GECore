#include "GECore/Core/Layer.h"

#include <GECore/Core/Application.h>
#include <GECore/Core/Input/Input.h>
#include <GECore/Core/Logger.h>

namespace GECore {

    Layer::Layer(std::string_view name) : BasicLayer(name) {
        if (cnt_get() == zui::counter::flag::empty) {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

            ImGui::StyleColorsDark();

            ImGuiStyle &style = ImGui::GetStyle();
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                style.WindowRounding = 0.0f;
                style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            }

            // Setup Platform/Renderer backends
            auto *window = Application::GetApplication()->getNativWindow();
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 410");
        }
        cnt_inc();
    }

    Layer::~Layer() {
        cnt_dec();
        if (cnt_get() == zui::counter::flag::empty) {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    }

    void Layer::ImGUIBeginRender() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void Layer::ImGUIEndRender() {
        ImGui::Render();

        ImGuiIO &io = ImGui::GetIO();
        auto app = Application::GetApplication();
        io.DisplaySize = ImVec2(static_cast<float>(app->getWidth()),
                                static_cast<float>(app->getHeight()));

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *currentWindow = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(currentWindow);
        }
    }

} // namespace GECore
