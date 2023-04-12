#include "GECore/Core/Window.h"

#include <memory>

#include <GECore/Core/Core.h>
#include <GECore/Core/Layer.h>
#include <GECore/Platform/OpenGL/Context.h>

#include <GECore/Core/Events/Close.h>
#include <GECore/Core/Events/CursorMove.h>
#include <GECore/Core/Events/KeyboardPress.h>
#include <GECore/Core/Events/MousePress.h>
#include <GECore/Core/Events/WindowResize.h>
#include "GECore/Core/Events/MouseScroll.h"
#include <string_view>

namespace GECore {

    void glfw_deleter(GLFWwindow *window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    Window::Window() {
        m_winProps.instance = this;

        ////////////////////////////////////////////////////////////////
        //
        // Create window context
        //
        ////////////////////////////////////////////////////////////////
        glfwSetErrorCallback([](int err, const char *description) {
            GE_CORE_ERROR("Glfw Error {0}: {1}", err, description);
        });

        GE_CORE_ASSERT(glfwInit(), "Window: glfwInit fail");

       glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
       glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
       glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

        m_winProps.window.reset(glfwCreateWindow(m_winProps.width, m_winProps.height,
                                                 m_winProps.name.data(), NULL, NULL));
        if (!m_winProps.window) {
            glfwTerminate();
            GE_CORE_ASSERT(0, "Window: context creation fail");
        }

        ////////////////////////////////////////////////////////////////
        //
        // Create OpenGL context
        //
        ////////////////////////////////////////////////////////////////
        // ToDo: code against an interface not an concrete implementation
        m_context = std::make_unique<OpenGLContext>(getWindow());
        glfwSetWindowUserPointer(getWindow(), &m_winProps);

        ////////////////////////////////////////////////////////////////
        //
        // Set callbacks
        //
        ////////////////////////////////////////////////////////////////
        glfwSetFramebufferSizeCallback(getWindow(),
                                       [](GLFWwindow *window, int width, int height) {
                                           glViewport(0, 0, width, height);
                                       });

        glfwSetWindowCloseCallback(m_winProps.window.get(), [](GLFWwindow *window) {
            Window *inst =
                    static_cast<WinProps *>(glfwGetWindowUserPointer(window))->instance;

            inst->on_event<close_e>();
        });

        glfwSetKeyCallback(
                m_winProps.window.get(),
                [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                    Window *inst =
                            static_cast<WinProps *>(glfwGetWindowUserPointer(window))->instance;

                    switch (action) {
                        case GLFW_PRESS: {
                            inst->on_event<keyboard_press_e>(false, key, scancode);
                            break;
                        }
                        case GLFW_RELEASE: {
                            break;
                        }
                    }
                });

        glfwSetScrollCallback(m_winProps.window.get(),
                              [](GLFWwindow *window, double xoffset, double yoffset) {
            Window* inst = static_cast<WinProps *>(glfwGetWindowUserPointer(window))->instance;
                                  inst->on_event<mouse_scroll_e>(false, xoffset, yoffset);
        });

        glfwSetMouseButtonCallback(
                m_winProps.window.get(),
                [](GLFWwindow *window, int button, int action, int mods) {
                    Window *inst =
                            static_cast<WinProps *>(glfwGetWindowUserPointer(window))->instance;

                    switch (action) {
                        case GLFW_PRESS: {
                            inst->on_event<mouse_press_e>(false, button);
                            break;
                        }
                        case GLFW_RELEASE: {
                            break;
                        }
                    }
                });

        glfwSetCursorPosCallback(
                m_winProps.window.get(),
                [](GLFWwindow *window, double xpos, double ypos) {
                    Window *inst =
                            static_cast<WinProps *>(glfwGetWindowUserPointer(window))->instance;

                    inst->on_event<cursor_move_e>(false, xpos, ypos);
                });

        glfwSetWindowSizeCallback(
                m_winProps.window.get(), [](GLFWwindow *window, int width, int height) {
                    Window *inst =
                            static_cast<WinProps *>(glfwGetWindowUserPointer(window))->instance;
                    WinProps *props =
                            static_cast<WinProps *>(glfwGetWindowUserPointer(window));

                    props->width = width;
                    props->height = height;
                    inst->on_event<window_resize_e>(width, height);
                });
    }

    void Window::setTitle(std::string_view name) noexcept {
        m_winProps.name = name;
        glfwSetWindowTitle(this->getWindow(), name.data());
    }

    Window::~Window() = default;

////////////////////////////////////////////////////////////////
//
// Render
//
////////////////////////////////////////////////////////////////
    void Window::render() {
        glfwPollEvents();
        m_context->swapBuffers();
    }

} // namespace GECore
