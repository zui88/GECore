#pragma once

#include <initializer_list>
#include <vector>
#include <utility>
#include <string>

#include "GECore/Core/Core.h"
#include "glad/glad.h"

namespace GECore {

class Buffer;
typedef Ref<Buffer> RefBuffer;

enum class ShaderDataType : uint32_t {
  None = 0U,
  Float,
  Float2,
  Float3,
  Float4,
  Mat3,
  Mat4,
  Int,
  Int2,
  Int3,
  Int4,
  Bool
};

static uint32_t GetElementSize(ShaderDataType type) {
  switch (type) {
  case ShaderDataType::Float:
    return 4;
  case ShaderDataType::Float2:
    return 4 * 2;
  case ShaderDataType::Float3:
    return 4 * 3;
  case ShaderDataType::Float4:
    return 4 * 4;
  case ShaderDataType::Mat3:
    return 4 * 3 * 3;
  case ShaderDataType::Mat4:
    return 4 * 4 * 4;
  case ShaderDataType::Int:
    return 4;
  case ShaderDataType::Int2:
    return 4 * 2;
  case ShaderDataType::Int3:
    return 4 * 3;
  case ShaderDataType::Int4:
    return 4 * 4;
  case ShaderDataType::Bool:
    return 1;
  case ShaderDataType::None:
  default:
    return 0;
  }
}

struct BufferElement {
  BufferElement(char const *name, ShaderDataType type,
                bool normalized = false) noexcept
      : name{ name }, type{ type }, size{ GetElementSize(type) }, normalized{ normalized } {}

  char const *name;
  ShaderDataType type;
  uint32_t size;
  uint32_t offset{ 0 };
  bool normalized;

  [[nodiscard]] uint32_t getElementCount() const;
};

class BufferLayout {
public:
  BufferLayout() {};
  
  // also with empty list callable
  BufferLayout(std::initializer_list<BufferElement> const &elements) noexcept
      : m_elements{ elements }, m_stride{ 0 } {
    calculate_offset_and_stride();
  }

  [[nodiscard]] bool isEmpty() const { return m_elements.empty(); };

  [[nodiscard]] std::vector<BufferElement> const &getElements() const {
    return m_elements;
  };

  [[nodiscard]] uint32_t getStride() const { return m_stride; };

private:
  friend Buffer;

  void calculate_offset_and_stride() noexcept {
    uint32_t offset{ 0 };

    for (auto &element : m_elements) {
      element.offset = offset;
      offset += element.size;
      m_stride += element.size;
    }
  }

  std::vector<BufferElement> m_elements;
  uint32_t m_stride;
};

class Buffer {
public:
  ~Buffer();

  void bind() const;

  static void unbind();

  /**
   * Allocate and fill block of memory with static data
   */
  void setData(void const *data, uint32_t size);

  /**
   * Allocate unizialized block of memory with dynamic data
   */
  void allocateData(uint32_t size);

  /**
   * Append geometry with the same vertex layout
   * @warning This function relys on dynamic data allocation
   */
  bool appendData(void const *data, uint32_t size);

  void flushData();

  void setLayout(BufferLayout layout);

  void dropLayout();

  [[nodiscard]] BufferLayout const &getLayout() const;

  static RefBuffer Create(uint32_t size);

  template <typename T, uint32_t count>
  static Ref<Buffer> Create(T const (&data)[count]) {
    auto vb = CreateRef<Buffer>();
    vb->open();
    auto size = count * sizeof(T);
    vb->setData(data, size);
    return vb;
  }

private:

  void open();

  void close();

  /**
   * Allocate memory in GPU domain with spezified draw mode
   */
  void set_data(void const *data, uint32_t size, GLenum draw_mode);

private:
  BufferLayout m_layout;
  uint32_t m_RendererID { 0 };
  uint32_t m_Size;
  /**
   * Number of entities accociated with their size in bytes builds a pair
   */
  std::vector<int32_t> m_Offset;
};

} // namespace GECore
