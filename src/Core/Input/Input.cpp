#include <exception>
#include <functional>
#include <stdexcept>
#include <utility>

#include "GECore/Core/Input/Input.h"

namespace GECore {

Input* Input::s_instance;
std::function<void*()> Input::s_currentWindowHandle;

Input &Input::GetInsatnce() {
  return *s_instance;
}

bool Input::IsKeyPressed(int keycode) {
  void* window { GetActiveWindow() };
  if (window && s_instance)
    return s_instance->isKeyPressed(window, keycode);
  throw "Input not properly instantiated";
}

bool Input::IsMouseButtonPressed(int key) {
  void* window { GetActiveWindow() };
  if (window && s_instance)
    return s_instance->isKeyPressed(window, key);
  throw "Input not properly instantiated";
}

double Input::GetCursorX() {
  void* window { GetActiveWindow() };
  if (window && s_instance)
    return s_instance->getCursorX(window);
  throw "Input not properly instantiated";
}
double Input::GetCursorY() {
  void* window { GetActiveWindow() };
  if (window && s_instance)
    return s_instance->getCursorY(window);
  throw "Input not properly instantiated";
}
std::pair<double, double> Input::GetCursorPosition() {
  void* window { GetActiveWindow() };
  if (window && s_instance)
    return s_instance->getCursorPosition(window);
  throw "Input not properly instantiated";
}

void* Input::GetActiveWindow() {
  return s_currentWindowHandle();
}

} // namespace GECore
