#include <GLFW/glfw3.h>

#include "GECore/Core/Input/GLFWInput.h"

namespace GECore {

bool GLFWInput::isKeyPressed(void* current_window, int keycode) {
  auto window { static_cast<GLFWwindow*>(current_window) };
  auto state  { glfwGetKey(window, keycode) };
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool GLFWInput::isMouseButtonPressed(void* current_window, int key) {
  auto window { static_cast<GLFWwindow*>(current_window) };
  auto state  { glfwGetMouseButton(window, key) };
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

double GLFWInput::getCursorX(void* current_window) {
  auto [x, y] = getCursorPosition(current_window);
  return x;
}

double GLFWInput::getCursorY(void* current_window) {
  auto [x, y] = getCursorPosition(current_window);
  return y;
}

std::pair<double, double> GLFWInput::getCursorPosition(void* current_window) {
  auto window { static_cast<GLFWwindow*>(current_window) };
  double x, y; 
  glfwGetCursorPos(window, &x, &y);
  return {x, y};
}

} // namespace GECore
