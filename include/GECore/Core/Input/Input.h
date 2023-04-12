#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <utility>

#include "Keycode.h"

namespace GECore {

  // enum class KeyCode : std::uint8_t {
  //   True = 0,
  //   False,
  //   Error
  // };

class Input {
public:
  ////////////////////////////////////////////////////////////////
  //
  // Interface
  //
  ////////////////////////////////////////////////////////////////
  static Input&    GetInsatnce();

  template<typename SpecializedInput>
  static void Init(std::function<void*()>&& current_window_handle);

  static bool                                           IsKeyPressed(int keycode);
  static bool                                           IsMouseButtonPressed(int key);
  static double                                         GetCursorX();
  static double                                         GetCursorY();
  static std::pair<double /* x */, double /* y */>      GetCursorPosition();

protected:
  ////////////////////////////////////////////////////////////////
  //
  // Singelton with inheritance
  //
  ////////////////////////////////////////////////////////////////
  Input() = default;
  ~Input() = default;

  // public because of weired error messages
public:
  Input(Input const&) = delete;		   // no assignment
  Input& operator=(Input const&) = delete; // no copy

private:
  ////////////////////////////////////////////////////////////////
  //
  // Specific template functions
  //
  ////////////////////////////////////////////////////////////////
  static void* GetActiveWindow();

  // Window must be casted according the underlying window system
  virtual bool                                          isKeyPressed(void* current_window, int keycode) = 0;
  virtual bool                                          isMouseButtonPressed(void* current_window, int key) = 0;
  virtual double                                        getCursorX(void* current_window) = 0;
  virtual double                                        getCursorY(void* current_window) = 0;
  virtual std::pair<double /* x */, double /* y */>     getCursorPosition(void* current_window) = 0;

private:
  ////////////////////////////////////////////////////////////////
  //
  // Fields
  //
  ////////////////////////////////////////////////////////////////
  static Input* s_instance;
  static std::function<void*()> s_currentWindowHandle;
};


////////////////////////////////////////////////////////////////
//
// Template definition
//
////////////////////////////////////////////////////////////////
template<typename SpecializedInput>
void Input::Init(std::function<void*()>&& current_window_handle) {
  if (!s_instance)
    s_instance = new SpecializedInput{};

  s_currentWindowHandle =
    std::forward<std::function<void*()>>(current_window_handle);
}


} // namespace GECore
