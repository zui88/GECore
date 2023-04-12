#include <GECore/Renderer/Renderer.h>
#include "GECore/Renderer/RenderCommand.h"
#include "GECore/Renderer/Renderer2D.h"

#include "glad/glad.h"

namespace GECore {

  Renderer::SceneData    *Renderer::s_SceneData  { new Renderer::SceneData{}    };
  Renderer::RendererData *Renderer::s_RenderData { new Renderer::RendererData{} };

  void Renderer::Open() {
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &s_RenderData->NumberOfTextureSlots);
    RenderCommand::StartUp();
    Renderer2D::Open();
  }

  int32_t Renderer::GetNumberOfTextureSlots() {
    return s_RenderData->NumberOfTextureSlots;
  }

  void Renderer::EndScene() {}

  void Renderer::Submit(RefVertexArray const &vao, const RefShader &shader,
                        glm::mat4 const &transform) {
    shader->bind();
    // todo :: once per scene
    shader->setMat4("u_VP", s_SceneData->ViewProjectionMatrix);
    // todo :: once per object
    shader->setMat4("u_Transform", transform);

    vao->bind();
    RenderCommand::DrawIndexed(vao);
  }

  void Renderer::BeginScene(const RefOrtographicCamera &camera) {
    s_SceneData->ViewProjectionMatrix = camera->getViewProjectionMatrix();
  }

  void Renderer::Close() {
    Renderer2D::Close();
    delete s_SceneData;
    delete s_RenderData;
  }

  } // namespace GECore
