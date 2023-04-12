//
// Created by zui on 2/12/23.
//

#include "GECore/Renderer/VertexArray.h"
#include "GECore/Core/Core.h"
#include "glad/glad.h"

namespace GECore {

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType const type) {
  switch (type) {
  case ShaderDataType::Float:
  case ShaderDataType::Float2:
  case ShaderDataType::Float3:
  case ShaderDataType::Float4:
  case ShaderDataType::Mat3:
  case ShaderDataType::Mat4:
    return GL_FLOAT;
  case ShaderDataType::Int:
  case ShaderDataType::Int2:
  case ShaderDataType::Int3:
  case ShaderDataType::Int4:
  case ShaderDataType::Bool:
    return GL_INT;
  case ShaderDataType::None:
  default:
    return GL_FALSE;
  }
}

void VertexArray::bind() const {
  glBindVertexArray(m_RendererID);
  m_Buffer->bind();
  m_IndexBuffer->bind();
}

void VertexArray::unbind() {
  glBindVertexArray(0);
  Buffer::unbind();
  IndexBuffer::unbind();
}

void VertexArray::add(RefIndexBuffer const &indexBuffer) {
  m_IndexBuffer = indexBuffer;
}

RefIndexBuffer VertexArray::getIndexBuffer() { return m_IndexBuffer; }

RefBuffer VertexArray::getBuffer() { return m_Buffer; }

void VertexArray::add(const RefBuffer &buffer) {

  GE_CORE_ASSERT(buffer->getLayout().getElements().size(), "Vetex buffer has no layout bound!");

  glBindVertexArray(m_RendererID);
  buffer->bind();

  int c = 0;
  auto const &elements = buffer->getLayout().getElements();
  for (auto const &element : elements) {
    glVertexAttribPointer(c, element.getElementCount(),
                          ShaderDataTypeToOpenGLBaseType(element.type),
                          element.normalized ? GL_TRUE : GL_FALSE,
                          buffer->getLayout().getStride(),
                          reinterpret_cast<void const *>(element.offset));
    glEnableVertexAttribArray(c);
    c++;
  }

  Buffer::unbind();
  glBindVertexArray(0);
  m_Buffer = buffer;
}

void VertexArray::flushData() {
  m_Buffer->flushData();
  m_IndexBuffer->flushData();
}

RefVertexArray VertexArray::Create() { return CreateRef<VertexArray>(); }

VertexArray::VertexArray() { glGenVertexArrays(1, &m_RendererID); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_RendererID); }

} // namespace GECore
