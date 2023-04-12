//
// Created by zui on 2/12/23.
//

#ifndef OGLGE_VERTEXARRAY_H
#define OGLGE_VERTEXARRAY_H

#include "GECore/Renderer/Buffer.h"
#include "GECore/Renderer/IndexBuffer.h"

namespace GECore {
class VertexArray;
typedef Ref<VertexArray> RefVertexArray;

class VertexArray {
public:

  VertexArray();

  ~VertexArray();

  void bind() const;

  static void unbind();

  RefIndexBuffer getIndexBuffer();
  
  RefBuffer getBuffer();

  void add(RefBuffer const &buffer);

  void add(RefIndexBuffer const &indexBuffer);

  void flushData();

  static RefVertexArray Create();

private:
  unsigned int m_RendererID;
  RefBuffer m_Buffer;
  RefIndexBuffer m_IndexBuffer;
};
} // namespace GECore
#endif // OGLGE_VERTEXARRAY_H
