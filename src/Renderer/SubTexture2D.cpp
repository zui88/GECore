#include "GECore/Renderer/SubTexture2D.h"
#include "GECore/Core/Core.h"
#include "glm/ext/vector_float2.hpp"

namespace GECore {

  SubTexture2D::SubTexture2D(Ref<Texture2D> const &texture, glm::vec2 const &min, glm::vec2 const &max)
    : m_Texture{ texture } {
    m_TexCoords[0] = { min.x, min.y };
    m_TexCoords[1] = { max.x, min.y };
    m_TexCoords[2] = { max.x, max.y };
    m_TexCoords[3] = { min.x, max.y };
  }

  Ref<SubTexture2D> SubTexture2D::Create(Ref<Texture2D> const &texture, glm::vec2 const &coords, glm::vec2 const &cellSize, glm::vec2 const &subTexSize) {
    glm::vec2 min { (coords.x * cellSize.x) / texture->getWidth(), (coords.y * cellSize.y) / texture->getHeight() };
    glm::vec2 max { ((coords.x + subTexSize.x) * cellSize.x) / texture->getWidth(), ((coords.y + subTexSize.y) * cellSize.y) / texture->getHeight() };
    return CreateRef<SubTexture2D>(texture, min, max);
  }

  glm::vec2 const *SubTexture2D::getCoords() const {
    return m_TexCoords;
  }

  Ref<Texture2D> const &SubTexture2D::getTexture() const {
    return m_Texture;
  }
}
