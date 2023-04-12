#pragma once

#include "GECore/Renderer/OrtographicCamera.h"
#include "GECore/Renderer/Shader.h"
#include "GECore/Renderer/VertexArray.h"

namespace GECore {

class Renderer;

typedef Scope<Renderer> ScopeRenderer;

class Renderer {
public:
  static void Open();

  static void Close();

  static void BeginScene(RefOrtographicCamera const &camera);

  static void EndScene();

  static void Submit(RefVertexArray const &, RefShader const &shader,
                     glm::mat4 const &transform = glm::mat4{1.0f});

  [[nodiscard]] static int32_t GetNumberOfTextureSlots();

private:
  struct RendererData {
    int32_t NumberOfTextureSlots;
  };

  struct SceneData {
    glm::mat4 ViewProjectionMatrix;
  };

  static SceneData *s_SceneData;
  static RendererData *s_RenderData;
};

} // namespace GECore
