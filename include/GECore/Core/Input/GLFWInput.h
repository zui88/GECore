#pragma once

#include "Input.h"

// client namespace
namespace GECore {

class GLFWInput : public Input {

  bool                                          isKeyPressed(void* current_window, int keycode)        override;
  bool                                          isMouseButtonPressed(void* current_window, int key)    override;
  double                                        getCursorX(void* current_window)                       override;
  double                                        getCursorY(void* current_window)                       override;
  std::pair<double /* x */, double /* y */>     getCursorPosition(void* current_window)                override;

};

} // namespace GECore
