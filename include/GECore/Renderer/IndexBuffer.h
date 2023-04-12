//
// Created by zui on 2/12/23.
//

#ifndef OGLGE_INDEXBUFFER_H
#define OGLGE_INDEXBUFFER_H

#include <vector>

#include "glad/glad.h"

#include "GECore/Core/Core.h"

namespace GECore {

class IndexBuffer;

typedef Ref<IndexBuffer> RefIndexBuffer;

class IndexBuffer {
public:
  ~IndexBuffer();

  void bind() const;

  static void unbind();

  [[nodiscard]] int32_t const *getIndicesCountsArray() const;

  [[nodiscard]] void const * const *getOffsetArray() const;

  [[nodiscard]] int32_t getGeometryCount() const;

  [[nodiscard]] int32_t const *getBaseVertexArray() const;

  [[nodiscard]] GLenum getIndexType() const;

  /**
   * Allocate and fill block of memory with static data
   */
  void setIndicies(uint32_t const *indices, int32_t count);

  /**
   * Allocate unizialized block of memory with dynamic data
   */
  void allocateIndicies(int32_t count);

  /**
   * Append geometry with the same vertex layout
   * @warning This function relys on dynamic data allocation
   */
  bool appendIndicies(uint32_t const *indices, uint32_t count, uint32_t vertices);

  void flushData();

  static RefIndexBuffer Create(uint32_t count);

  template <uint32_t count>
  static RefIndexBuffer Create(uint32_t const (&indicies)[count]) {
    auto ib = CreateRef<IndexBuffer>();
    ib->open();
    ib->setIndicies(indicies, count);
    return ib;
  }

private:
  void open();

  void close();

  void set_indicies(void const *indices, uint32_t count, GLenum draw_mode);

private:
  uint32_t m_RendererID { 0 };
  GLenum m_IndicesType { GL_UNSIGNED_INT };
  uint32_t m_Size;
  std::vector<void const*> m_IndiciesOffset;
  std::vector<int32_t> m_IndicesCounts;
  std::vector<int32_t> m_BaseVertex;
};

} // namespace GECore

#endif // INDEX_BUFFER_H
