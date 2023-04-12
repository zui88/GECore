#pragma once

#include "BasicLayer.h"

#include <string_view>
#include <zui/util/counter.h>

// OpenGl bound
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

namespace GECore {

    class Application;

// default: GLSL version 410
    class Layer : public BasicLayer, zui::static_counter<Layer> {
    public:
        Layer(std::string_view name = "ImGui Layer");

        virtual ~Layer();

        virtual void onKeyboardPress(keyboard_press_e &e) override {}

        virtual void OnMousePress(mouse_press_e &) override {}

        virtual void onMouseScroll(mouse_scroll_e &) override {}

        virtual void onCursorMove(cursor_move_e &) override {}

        virtual void onWindowResize(window_resize_e &) override {}

        virtual void update(Time time) override {}

        virtual void imguirender() override final {
            Layer::ImGUIBeginRender();
            ImGUIRender();
            Layer::ImGUIEndRender();
        }

        virtual void ImGUIRender() {};

        virtual void attach() override {};

        virtual void detach() override {};

    private:
        // ImGUI Render
        static void ImGUIBeginRender();

        static void ImGUIEndRender();
    };

} // namespace GECore
