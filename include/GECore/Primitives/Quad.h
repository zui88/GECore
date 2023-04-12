#ifndef Quad_H
#define Quad_H

#include "GECore/Primitives/Vertex.h"

namespace GECore {

class Quad {
public:
  Quad() : Quad(0.f, 0.f, 0.f, 1.f) {};

  explicit Quad(glm::vec3 const& position) : Quad(position.x, position.y, position.z, 1.f) {}

  explicit Quad(glm::vec4 const& color) : Quad(color.r, color.g, color.b, color.a) {}

  explicit Quad(glm::vec3 const& position, glm::vec4 const& color)
    : Quad(position.x, position.y, position.z, color.r, color.g, color.b, color.a) {}

  Quad(float r, float g, float b, float alpha) : Quad(0.f, 0.f, 0.f, r, g, b, alpha) {}

  Quad(float x, float y, float z, float r, float g, float b, float alpha) {
    m_Vertices[0].position = glm::vec3{ x, y, 0.0f };
    m_Vertices[1].position = glm::vec3{ x, y, 0.0f };
    m_Vertices[2].position = glm::vec3{ x, y, 0.0f };
    m_Vertices[3].position = glm::vec3{ x, y, 0.0f };
    m_Vertices[0].texcoord = glm::vec2{ 0.0f, 0.0f };
    m_Vertices[1].texcoord = glm::vec2{ 1.0f, 0.0f };
    m_Vertices[2].texcoord = glm::vec2{ 1.0f, 1.0f };
    m_Vertices[3].texcoord = glm::vec2{ 0.0f, 1.0f };
    m_Vertices[0].color = glm::vec4{ r, g, b, alpha };
    m_Vertices[1].color = glm::vec4{ r, g, b, alpha };
    m_Vertices[2].color = glm::vec4{ r, g, b, alpha };
    m_Vertices[3].color = glm::vec4{ r, g, b, alpha };
  }

  void setTexIndex(float idx);

  void setTilingFactor(float tf);

  void setTexCoords(glm::vec2 const *coords);

  void size(glm::vec2 const &s);

  void const *vertexData() const { return m_Vertices; }

  uint32_t vertexCount()   const { return sizeof(m_Vertices) / sizeof(Vertex); }

  uint32_t const *indexData() const { return m_Indicies; }

  uint32_t indexCount()       const { return sizeof(m_Indicies) / sizeof(uint32_t); }

private:
  Vertex   m_Vertices[4];
  uint32_t m_Indicies[6] = { 0, 1, 2, 2, 3, 0 };
};

} /* GECore */

#endif /* Quad_H */
