#pragma once

#include <string_view>
#include <memory>

#include "GECore/Core/Time.h"

#include "Events/CursorMove.h"
#include "Events/KeyboardPress.h"
#include "Events/MousePress.h"
#include "Events/WindowResize.h"
#include "Events/MouseScroll.h"

namespace GECore {

class BasicLayer;
typedef std::shared_ptr<BasicLayer> Layer_H;
typedef std::weak_ptr<BasicLayer>   layer_whandle;


class BasicLayer {
public:
  BasicLayer() = default;
  virtual ~BasicLayer() = default;
  BasicLayer(std::string_view name) : m_name{ name } { }

  virtual void attach()            =    0;
  virtual void detach()            =    0;
  virtual void update(Time time)   =    0;
  virtual void imguirender()       =    0;

  virtual void onKeyboardPress(keyboard_press_e&)       =    0;
  virtual void onMouseScroll  (mouse_scroll_e&)         =    0;
  virtual void OnMousePress   (mouse_press_e&)          =    0;
  virtual void onCursorMove   (cursor_move_e&)          =    0;
  virtual void onWindowResize (window_resize_e&)        =    0;

  inline std::string_view getName() const { return m_name; }

private:
  std::string_view m_name{ "debug" };
};

} // namespace GECore
