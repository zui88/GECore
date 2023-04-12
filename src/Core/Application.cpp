#include <memory>
#include <string_view>
#include <cstdlib>


#include "GECore/Core/Core.h"
#include "GECore/Core/Application.h"
#include "GECore/Core/Input/GLFWInput.h"
#include "GECore/Core/Window.h"


#include "GECore/Renderer/Renderer.h"


#include "GLFW/glfw3.h"


namespace GECore {


    Application::Properties Application::s_Properties;


    Application::Properties const &Application::GetProperties() {
      return s_Properties;
    }


    Application::application_t Application::GetApplication() {
        return s_Application;
    }


    Application::Application(int width, int height, std::string_view name)
            : Application::Application(name) {
        m_Window->setHeight(height);
        m_Window->setWidth(width);
    }


    Application::Application(std::string_view name) : Application::Application() {
        m_Window->setTitle(name);
    }


    Application::Application() { open(); }


    void Application::open() {
        // standart asset path
        s_Properties.assetPath = "/home/zui/Programming/GraphicEngine/gecore/assets";
        const char* ap = std::getenv("GECORE");
        if (ap) {
	  s_Properties.assetPath = ap;
	}
      	
	GE_CORE_ASSERT(!s_Application, "Application: already exists");
        s_Application = this;

        m_Window = std::make_unique<Window>();

        Input::Init<GLFWInput>([this]() {
            auto window = this->getNativWindow();
            GE_CORE_ASSERT(window, "Input: no bound window context");
            return static_cast<void *>(window);
        });

	Renderer::Open();

        m_Window->subscribe<close_e, &Application::windowCloseEvent>(*this);
        m_Window->subscribe<mouse_press_e, &Application::mousePressEvent>(*this);
        m_Window->subscribe<cursor_move_e, &Application::cursorMoveEvent>(*this);
        m_Window->subscribe<keyboard_press_e, &Application::keyboardPressEvent>(*this);
        m_Window->subscribe<window_resize_e, &Application::windowResizeEvent>(*this);
        m_Window->subscribe<mouse_scroll_e, &Application::mouseScrollEvent>(*this);

    }


    Application::~Application() {
        GE_CORE_TRACE("Application: Shut down");
        m_LayerStack.clear_container();
        Renderer::Close();
    }
     

    NativWindow Application::getNativWindow() { return m_Window->getWindow(); }
									       

    int Application::getWidth() { return m_Window->getWidth(); }
								

    int Application::getHeight() { return m_Window->getHeight(); }
								  

    void Application::windowCloseEvent() {
        GE_CORE_INFO("An Close Event occured");
        m_IsRunning = false;
    }
     

    void Application::mouseScrollEvent(mouse_scroll_e &e) {
        auto layer = m_LayerStack.end();
        if (!m_LayerStack.is_empty()) {
            do {
                layer--;
                (*layer)->onMouseScroll(e);
            } while (layer != m_LayerStack.begin());
        }
    }
     

    void Application::windowResizeEvent(window_resize_e &e) {
//        GE_CORE_INFO("Window Resize---width: {0}; height: {1}", e.width, e.height);
//        glViewport(0, 0, e.width, e.height);
        // reverse iteration
        auto layer = m_LayerStack.end();
        if (!m_LayerStack.is_empty()) {
            do {
                layer--;
                (*layer)->onWindowResize(e);
            } while (layer != m_LayerStack.begin());
        }
    }
     

// user events
    void Application::mousePressEvent(mouse_press_e &e) {
        // reverse iteration
        auto layer = m_LayerStack.end();
        if (!m_LayerStack.is_empty()) {
            do {
                layer--;
                (*layer)->OnMousePress(e);
                if (e.handled) {
                    break;
                }
            } while (layer != m_LayerStack.begin());
        }
    }
     

    void Application::cursorMoveEvent(cursor_move_e &e) {
        // reverse iteration
        auto layer = m_LayerStack.end();
        if (!m_LayerStack.is_empty()) {
            do {
                layer--;
                (*layer)->onCursorMove(e);
                if (e.handled) {
                    break;
                }
            } while (layer != m_LayerStack.begin());
        }
    }
     

    void Application::keyboardPressEvent(keyboard_press_e &e) {
        // reverse iteration
        auto layer = m_LayerStack.end();
        if (!m_LayerStack.is_empty()) {
            do {
                layer--;
                (*layer)->onKeyboardPress(e);
                if (e.handled) {
                    break;
                }
            } while (layer != m_LayerStack.begin());
        }
    }
     

    void Application::updateLayer(Time time) {
        if (!m_LayerStack.is_empty()) {
            for (auto &layer: m_LayerStack) {
                layer->update(time);
            }
        }
    }
     

    void Application::run() {
        Time::type time;
        while (m_IsRunning) {
            time = (Time::type) glfwGetTime(); // ToDo: Platform::GetTime();
            Time dt = time - m_LastTimeStep;
            m_LastTimeStep = time;

            updateLayer(dt);

            ImGUIRender();

            m_Window->render();
        }
    }
     

    Layer_H Application::popLayer(Layer_H const &layer) {
        auto tmp_layer = m_LayerStack.pop_layer(layer);
        if (tmp_layer) {
            tmp_layer->detach();
            return tmp_layer;
        }
        return Layer_H{};
    }
     

    Layer_H Application::popOverlay(Layer_H const &layer) {
        auto tmp_layer = m_LayerStack.pop_overlay(layer);
        if (tmp_layer) {
            tmp_layer->detach();
            return tmp_layer;
        }
        return Layer_H{};
    }
     

    void Application::ImGUIRender() {
        if (!m_LayerStack.is_empty()) {
            for (auto &layer: m_LayerStack) {
                layer->imguirender();
            }
        }
    }
     

} // namespace GECore
