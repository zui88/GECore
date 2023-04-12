//
// Created by zui on 2/15/23.
//

#ifndef OGLGE_RENDERER2D_H
#define OGLGE_RENDERER2D_H

#include "GECore/Renderer/OrtographicCamera.h"
#include "GECore/Renderer/Texture2D.h"
#include "GECore/Renderer/SubTexture2D.h"
#include "glm/glm.hpp"

namespace GECore {


class Renderer2D {
public:
  static void Open();


  static void Close();


  static void BeginScene(Ref<OrtographicCamera> const &camera);


  static void EndScene();


  static void Flush();


  static void DrawQuad(glm::vec2 const &position, glm::vec2 const &size,
                       glm::vec4 const &color);


  static void DrawQuad(glm::vec3 const &position, glm::vec2 const &size,
                       glm::vec4 const &color);


  static void DrawQuad(glm::vec2 const &position, glm::vec2 const &size,
                       Ref<Texture2D> const &texture, float tilingFactor = 1.0f,
                       glm::vec4 const &tintColor = glm::vec4{ 1.0f });


  static void DrawQuad(glm::vec3 const &position, glm::vec2 const &size,
                       Ref<Texture2D> const &texture, float tilingFactor = 1.0f,
                       glm::vec4 const &tintColor = glm::vec4{ 1.0f });


  static void DrawQuad(glm::vec2 const &position, glm::vec2 const &size,
                       Ref<SubTexture2D> const &texture, float tilingFactor = 1.0f,
                       glm::vec4 const &tintColor = glm::vec4{ 1.0f });


  static void DrawQuad(glm::vec3 const &position, glm::vec2 const &size,
                       Ref<SubTexture2D> const &texture, float tilingFactor = 1.0f,
                       glm::vec4 const &tintColor = glm::vec4{ 1.0f });


  static void ResetStatistics();


  struct Statistics {
    uint32_t DrawCalls, Quads, Vertcies, Indecies;
  };


  static Statistics GetStatistics();


};

} // namespace GECore

#endif // OGLGE_RENDERER2D_H
