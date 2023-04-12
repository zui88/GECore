#pragma once

#include "GECore/Renderer/GraphicContext.h"

struct GLFWwindow;

namespace GECore {

class OpenGLContext : public GraphicContext<GLFWwindow> {
public:
  OpenGLContext(GLFWwindow *window);
  ~OpenGLContext() = default;

  void makeCurrent() override;
  void swapBuffers() override;
};

} // namespace GECore
