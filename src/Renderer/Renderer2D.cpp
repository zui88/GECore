//
// Created by zui on 2/15/23.
//


#include "GECore/Renderer/Renderer2D.h"
#include "GECore/Core/Logger.h"
#include "GECore/Renderer/Renderer.h"
#include "GECore/Renderer/RenderCommand.h"
#include "GECore/Renderer/Shader.h"
#include "GECore/Renderer/VertexArray.h"
#include "GECore/Core/Application.h"


#include "GECore/Primitives/Quad.h"
#include <cstdint>


namespace GECore {


struct Renderer2DStorage {
  static constexpr uint32_t MAX_QUADS    = 10000;
  static constexpr uint32_t MAX_VERTICES = MAX_QUADS * 4;
  static constexpr uint32_t MAX_INDICES  = MAX_QUADS * 6;
  uint32_t MAX_TEXUTURE_SLOTS;
  Quad DefaultQuad;

  Ref<VertexArray> QVA;
  Ref<Shader>      TextureShader;
  Ref<Texture2D>   WhiteTexture;

  std::vector<Ref<Texture2D>> TextureSlots;
  uint32_t TextureSlotIndex = 1; // 0 = white texture

  glm::mat4 UTransform = glm::mat4{ 1.f };

  struct Statistics {
    uint32_t getTotalDrawCount() const { return DrawCalls; }
    uint32_t getTotalQuadCount() const { return QuadCount; }
    uint32_t getTotalVertexCount() const { return QuadCount * 4; }
    uint32_t getTotalIndexCount() const { return QuadCount * 6; }
  private:
    friend Renderer2D;
    uint32_t DrawCalls = 0;
    uint32_t QuadCount = 0;
  } Stats;
};


static Scope<Renderer2DStorage> s_Data;


void Renderer2D::ResetStatistics() {
  s_Data->Stats.DrawCalls = 0;
  s_Data->Stats.QuadCount = 0;
}


Renderer2D::Statistics Renderer2D::GetStatistics() {
  auto quads = s_Data->Stats.getTotalQuadCount();
  auto draws = s_Data->Stats.getTotalDrawCount();
  auto verticies = s_Data->Stats.getTotalVertexCount();
  auto indicies = s_Data->Stats.getTotalIndexCount();
  return { draws, quads, verticies, indicies };
}


void Renderer2D::Open() {
  s_Data = CreateScope<Renderer2DStorage>();
  s_Data->QVA = VertexArray::Create();
  auto buffer = Buffer::Create(Renderer2DStorage::MAX_VERTICES * sizeof(Vertex));
  buffer->setLayout({{"a_Pos",          ShaderDataType::Float3},
                     {"a_TexCoord",     ShaderDataType::Float2},
		     {"a_Color",        ShaderDataType::Float4},
		     {"a_TexIndex",     ShaderDataType::Float },
		     {"a_TilingFactor", ShaderDataType::Float }
    });
  s_Data->QVA->add(buffer);
  auto ibuffer = IndexBuffer::Create(Renderer2DStorage::MAX_INDICES);
  s_Data->QVA->add(ibuffer);

  s_Data->WhiteTexture = CreateRef<Texture2D>(1u, 1u);
  uint32_t whiteTextureData = 0xFFFFFFFF;
  s_Data->WhiteTexture->setData(&whiteTextureData, sizeof(whiteTextureData));

  // todo: make a asset system
  std::string assetPath{ Application::GetProperties().assetPath };
  s_Data->TextureShader = Shader::Create("TextureShader", (assetPath + "/" + "texture.glsl.vert").c_str(), (assetPath + "/" + "texture.glsl.frag").c_str());
  s_Data->TextureShader->bind();
  s_Data->MAX_TEXUTURE_SLOTS = Renderer::GetNumberOfTextureSlots();
  GE_CORE_INFO("Renderer2D -> Max Texture Slots: {}", s_Data->MAX_TEXUTURE_SLOTS);
  s_Data->TextureSlots.resize(s_Data->MAX_TEXUTURE_SLOTS);
  int32_t samplers[s_Data->MAX_TEXUTURE_SLOTS];
  for (uint32_t i = 0; i < s_Data->MAX_TEXUTURE_SLOTS; i++) {
    samplers[i] = i;
  }
  s_Data->TextureSlots[0] = s_Data->WhiteTexture;
  s_Data->TextureShader->setIntArray("u_Textures", samplers, s_Data->MAX_TEXUTURE_SLOTS);
  s_Data->TextureShader->setMat4("u_Transform", s_Data->UTransform);
}


void Renderer2D::Close() {
  s_Data.reset();
}


void Renderer2D::BeginScene(const Ref<OrtographicCamera> &camera) {
  s_Data->TextureShader->bind();
  s_Data->TextureShader->setMat4("u_VP", camera->getViewProjectionMatrix());
}


void Renderer2D::EndScene() {
  Renderer2D::Flush();
}


void Renderer2D::Flush() {
  if (s_Data->QVA->getIndexBuffer()->getGeometryCount()) {
    for (uint32_t i = 0; i < s_Data->TextureSlotIndex; i++) {
      s_Data->TextureSlots[i]->setSlot(i);
      s_Data->TextureSlots[i]->bind();
    }
    RenderCommand::DrawIndexed(s_Data->QVA);
    s_Data->QVA->flushData();
    s_Data->TextureSlotIndex = 1;
    s_Data->Stats.DrawCalls++;
  }
}


void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
  s_Data->Stats.QuadCount++;

  float whiteTextureIndex{ 0.0f };
  Quad quad{ position, color };
  quad.size(size);
  quad.setTexIndex(whiteTextureIndex);

  s_Data->QVA->getBuffer()->appendData(quad.vertexData(), sizeof(Vertex) * 4);
  s_Data->QVA->getIndexBuffer()->appendIndicies(quad.indexData(), quad.indexCount(), quad.vertexCount());

  if(s_Data->QVA->getIndexBuffer()->getGeometryCount() >= Renderer2DStorage::MAX_QUADS) {
    Renderer2D::Flush();
  }
}


void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
  Renderer2D::DrawQuad({position.x, position.y, 0.f}, size, color);
}


void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor, glm::vec4 const &tintColor) {
  Renderer2D::DrawQuad({position.x, position.y, 0.f}, size, texture, tilingFactor, tintColor);
}


void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor, glm::vec4 const &tintColor) {
  s_Data->Stats.QuadCount++;

  // search for equal texture in texture slot array
  float textureIndex{ 0.0f };
  for (uint32_t i = 1; i < s_Data->TextureSlotIndex; i++) {
    // todo: function for comparing assets
    if (*s_Data->TextureSlots[i].get() == *texture.get()) {
      textureIndex = static_cast<float>(i);
      break;
    }
  }
  // not found -> add new texture into texture slot -> increment texture index pointer
  if (textureIndex == 0.0f) {
    textureIndex = static_cast<float>(s_Data->TextureSlotIndex);
    s_Data->TextureSlots[s_Data->TextureSlotIndex] = texture;
    s_Data->TextureSlotIndex++;
  }
  
  Quad quad{ position, tintColor };
  quad.size(size);
  quad.setTexIndex(textureIndex);
  quad.setTilingFactor(tilingFactor);

  s_Data->QVA->getBuffer()->appendData(quad.vertexData(), sizeof(Vertex) * 4);
  s_Data->QVA->getIndexBuffer()->appendIndicies(quad.indexData(), quad.indexCount(), quad.vertexCount());

  if(s_Data->QVA->getIndexBuffer()->getGeometryCount() >= Renderer2DStorage::MAX_QUADS ||
     s_Data->TextureSlotIndex >= s_Data->MAX_TEXUTURE_SLOTS) {
    Renderer2D::Flush();
  }
}


  void Renderer2D::DrawQuad(glm::vec2 const &position, glm::vec2 const &size, Ref<SubTexture2D> const &texture, float tilingFactor, glm::vec4 const &tintColor) {
    Renderer2D::DrawQuad({ position.x, position.y , 0.f }, size, texture, tilingFactor, tintColor);
    }


  void Renderer2D::DrawQuad(glm::vec3 const &position, glm::vec2 const &size, Ref<SubTexture2D> const &subTexture, float tilingFactor, glm::vec4 const &tintColor) {
  s_Data->Stats.QuadCount++;

  auto texture = subTexture->getTexture();

  // search for equal texture in texture slot array
  float textureIndex{ 0.0f };
  for (uint32_t i = 1; i < s_Data->TextureSlotIndex; i++) {
    // todo: function for comparing assets
    if (*s_Data->TextureSlots[i].get() == *texture.get()) {
      textureIndex = static_cast<float>(i);
      break;
    }
  }
  // not found -> add new texture into texture slot -> increment texture index pointer
  if (textureIndex == 0.0f) {
    textureIndex = static_cast<float>(s_Data->TextureSlotIndex);
    s_Data->TextureSlots[s_Data->TextureSlotIndex] = texture;
    s_Data->TextureSlotIndex++;
  }
  
  Quad quad{ position, tintColor };
  quad.size(size);
  quad.setTexIndex(textureIndex);
  quad.setTilingFactor(tilingFactor);
  quad.setTexCoords(subTexture->getCoords());

  s_Data->QVA->getBuffer()->appendData(quad.vertexData(), sizeof(Vertex) * 4);
  s_Data->QVA->getIndexBuffer()->appendIndicies(quad.indexData(), quad.indexCount(), quad.vertexCount());

  if(s_Data->QVA->getIndexBuffer()->getGeometryCount() >= Renderer2DStorage::MAX_QUADS ||
     s_Data->TextureSlotIndex >= s_Data->MAX_TEXUTURE_SLOTS) {
    Renderer2D::Flush();
  }
  }


} // namespace GECore
