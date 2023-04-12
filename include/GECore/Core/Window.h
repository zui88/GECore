#pragma once

#include <functional>
#include <memory>
#include <string_view>

#include <entt/signal/dispatcher.hpp>

// Forward declaration
struct GLFWwindow;

namespace GECore {

// Forward declaration
class Window;
// OpenGL or Vulkan
template <typename NativContext> class GraphicContext;

void glfw_deleter(GLFWwindow *);

// own instance for glfw data attrib pointer
struct WinProps {
  int width = 640, height = 480;
  std::string_view name = "GECore Graphic Engine";
  std::unique_ptr <GLFWwindow, std::function<void(GLFWwindow *)>> window{nullptr, &glfw_deleter};
  Window *instance = nullptr;
};

// At every window switch GLFW Attrib Pointer must be reset
class Window {
  typedef entt::dispatcher Dispatcher;

public:
  /* Creates a context and makes it current */
  Window();
  // because of window context up, the underlying type is completely known in cpp file
  ~Window();

  void render();
  template <typename Event, auto MemFunP, typename T> void subscribe(T &inst) {
    m_dispatcher.sink<Event>().template connect<MemFunP>(inst);
  }

  [[nodiscard]] GLFWwindow *getWindow() noexcept {
    return m_winProps.window.get();
  }
  [[nodiscard]] int getHeight() noexcept { return m_winProps.height; }
  [[nodiscard]] int getWidth() noexcept { return m_winProps.width; }

  void setTitle(std::string_view name) noexcept;
  void setWidth(int width) noexcept { m_winProps.width = width; }
  void setHeight(int height) noexcept { m_winProps.height = height; }

private:
  template <typename Event, typename... Args> void on_event(Args &&...args) {
    m_dispatcher.trigger(Event{std::forward<Args>(args)...});
  }

  template <typename Event> void on_event() { m_dispatcher.trigger<Event>(); }

  ////////////////////////////////////////////////////////////////
  //
  // Fields
  //
  ////////////////////////////////////////////////////////////////
  Dispatcher m_dispatcher;
  WinProps m_winProps;
  // can be different i.e. for OpenGL or Vulkan
  std::unique_ptr<GraphicContext<GLFWwindow>> m_context;
};

} // namespace GECore

