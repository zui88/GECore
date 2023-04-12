//
// Created by zui on 2/12/23.
//

#include "GECore/Renderer/IndexBuffer.h"
#include "GECore/Core/Logger.h"
#include <cstdint>

namespace GECore {

IndexBuffer::~IndexBuffer() {
  if (m_RendererID) {
    close();
  }
}

void IndexBuffer::open() { glGenBuffers(1, &m_RendererID); }

void IndexBuffer::close() { glDeleteBuffers(1, &m_RendererID); }

GLenum IndexBuffer::getIndexType() const { return m_IndicesType; }

void const * const *IndexBuffer::getOffsetArray() const {
  return m_IndiciesOffset.data();
}

int32_t const *IndexBuffer::getIndicesCountsArray() const {
  return m_IndicesCounts.data();
}

void IndexBuffer::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void IndexBuffer::setIndicies(uint32_t const *indices, int32_t count) {
  this->set_indicies(indices, count, GL_STATIC_DRAW);
}

bool IndexBuffer::appendIndicies(uint32_t const *indices, uint32_t count, uint32_t vertices) {
  auto offset { reinterpret_cast<std::uintptr_t>(m_IndiciesOffset.back()) };
  if ((offset + count * sizeof(int32_t)) <= m_Size) {
    if (m_BaseVertex.size() == 1) {
      m_BaseVertex.push_back(vertices);
      m_IndicesCounts.push_back(count);
    } else {
      m_IndiciesOffset.push_back(reinterpret_cast<void const *>(m_IndicesCounts.back() * sizeof(int32_t)));
      m_BaseVertex.push_back(m_BaseVertex.back() + vertices);
      m_IndicesCounts.push_back(count);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
		    reinterpret_cast<std::intptr_t>(m_IndiciesOffset.back()),
		    count * sizeof(int32_t),
		    indices);
    return true;
  }
  return false;
}

void IndexBuffer::flushData() {
  m_IndiciesOffset.clear();
  m_IndiciesOffset.push_back(reinterpret_cast<void const *>(0));
  m_BaseVertex.clear();
  m_BaseVertex.push_back(0);
  m_IndicesCounts.clear();
  // m_IndicesCounts.push_back(0);
}

int32_t const *IndexBuffer::getBaseVertexArray() const {
  return m_BaseVertex.data();
}

int32_t IndexBuffer::getGeometryCount() const {
  return m_IndicesCounts.size();
}

void IndexBuffer::allocateIndicies(int32_t count) {
  this->set_indicies(nullptr, count, GL_DYNAMIC_DRAW);
}

void IndexBuffer::set_indicies(void const *indices, uint32_t count, GLenum draw_mode) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
  m_Size = sizeof(int32_t) * count;
  this->flushData();
  m_IndicesCounts.push_back(count);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Size, indices, draw_mode);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

RefIndexBuffer IndexBuffer::Create(uint32_t count) {
  auto ib = CreateRef<IndexBuffer>();
  ib->open();
  ib->allocateIndicies(count);
  return ib;
}

} // namespace GECore
