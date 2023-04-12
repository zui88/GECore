#pragma once

#include "glm/ext/vector_float2.hpp"
#include "glm/glm.hpp"

#include "GECore/Core/Core.h"
#include "GECore/Renderer/Texture2D.h"

namespace GECore {

class SubTexture2D {
public:
  SubTexture2D(Ref<Texture2D> const &texture, glm::vec2 const &min, glm::vec2 const &max);

  static Ref<SubTexture2D> Create(Ref<Texture2D> const &texture, glm::vec2 const &coords, glm::vec2 const &subTextureSize, glm::vec2 const &subTexSize = { 1, 1 });

  glm::vec2 const *getCoords() const;

  Ref<Texture2D> const &getTexture() const;

private:
  Ref<Texture2D> m_Texture;
  glm::vec2 m_TexCoords[4];
};

} // namespace GECore
