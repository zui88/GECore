//
// Created by zui on 2/6/23.
//

#ifndef OGLGE_RENDERCOMMAND_H
#define OGLGE_RENDERCOMMAND_H

#include "GECore/Core/Color.h"
#include "GECore/Renderer/VertexArray.h"

namespace GECore {

class RenderCommand {
public:
  static void Clear();

  static void ClearColor(COLOR color = COLOR::BLACK);

  static void StartUp();

  static void DrawIndexed(Ref<VertexArray> const& vertexArray);
};

} // namespace GECore

#endif // OGLGE_RENDERCOMMAND_H
