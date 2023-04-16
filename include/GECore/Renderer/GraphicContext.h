#pragma once

namespace GECore {

template <typename Window>
class GraphicContext {
public:
  GraphicContext(Window *window) : m_window{ window } {}

  virtual void makeCurrent() = 0;
  virtual void swapBuffers() = 0;

protected:
  // no spcial ownership
  Window *m_window;
};

} // namespace GECore
