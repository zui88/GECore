#include "GECore/Renderer/Buffer.h"
#include "GECore/Core/Logger.h"

#include <sstream>

namespace GECore {

uint32_t BufferElement::getElementCount() const {
  switch (type) {
  case ShaderDataType::Float:
    return 1;
  case ShaderDataType::Float2:
    return 2;
  case ShaderDataType::Float3:
    return 3;
  case ShaderDataType::Float4:
    return 4;
  case ShaderDataType::Mat3:
    return 3 * 3;
  case ShaderDataType::Mat4:
    return 4 * 4;
  case ShaderDataType::Int:
    return 1;
  case ShaderDataType::Int2:
    return 2;
  case ShaderDataType::Int3:
    return 3;
  case ShaderDataType::Int4:
    return 4;
  case ShaderDataType::Bool:
    return 1;
  case ShaderDataType::None:
  default:
    GE_CORE_ASSERT(false, "Unknown shader data type");
    return 0;
  }
}

 void Buffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }

void Buffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

bool Buffer::appendData(void const *data, uint32_t size) {
  uint32_t lastOffset = m_Offset.back();
  uint32_t offset = lastOffset + size;
  if (offset <= m_Size) {
    m_Offset.push_back(offset);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ARRAY_BUFFER, lastOffset, size, data);
    return true;
  }
  return false;
}

  BufferLayout const &Buffer::getLayout() const {
    return m_layout;
  }

void Buffer::flushData() {
  m_Offset.clear();
  m_Offset.push_back(0U);
}

void Buffer::open() { glGenBuffers(1, &m_RendererID); }

void Buffer::close() { glDeleteBuffers(1, &m_RendererID); }

Buffer::~Buffer() {
  if (m_RendererID) {
    this->close();
  }
}

void Buffer::set_data(void const *data, uint32_t size, GLenum draw_mode) {
  m_Offset.clear();
  m_Offset.push_back(0u);
  m_Size = size;
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
  glBufferData(GL_ARRAY_BUFFER, size, data, draw_mode);
  // GLenum err;
  // while((err = glGetError()) != GL_NO_ERROR)
  // {
  // GE_CORE_ERROR("Buffer @ OpenGL Error: {}", err);
  // }
}

void Buffer::setData(void const *data, uint32_t size) {
  this->set_data(data, size, GL_STATIC_DRAW);
}

void Buffer::allocateData(uint32_t size) {
  this->set_data(nullptr, size, GL_DYNAMIC_DRAW);
}

RefBuffer Buffer::Create(uint32_t size) {
  auto vb = CreateRef<Buffer>();
  vb->open();
  vb->allocateData(size);
  return vb;
}

void Buffer::setLayout(BufferLayout layout) { m_layout = layout; }

[[maybe_unused]] void Buffer::dropLayout() {
  BufferLayout layout;
  m_layout = layout;
}

} // namespace GECore
