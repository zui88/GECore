//
// Created by zui on 2/15/23.
//


#include "Layer.h"
#include "GECore/Core/Application.h"
#include "GECore/Renderer/Renderer2D.h"
#include "imgui.h"


void TestLayer::attach() {
    m_CameraController = GECore::OrtographicCameraController::Create(1.f);
    auto ap{ GECore::Application::GetProperties().assetPath };
    m_Texture[0] = GECore::Texture2D::Create(ap + "/" + "sun.png");
    m_Texture[1] = GECore::Texture2D::Create(ap + "/" + "sailor-moon.png");
    auto spriteSheet = GECore::Texture2D::Create(ap + "/" + "Attack_1.png");
    m_Sprite[0] = GECore::SubTexture2D::Create(spriteSheet, { 0, 0 }, { 128, 128 });
    m_Sprite[1] = GECore::SubTexture2D::Create(spriteSheet, { 1, 0 }, { 128, 128 });
    m_Sprite[2] = GECore::SubTexture2D::Create(spriteSheet, { 2, 0 }, { 128, 128 });
    m_Sprite[3] = GECore::SubTexture2D::Create(spriteSheet, { 3, 0 }, { 128, 128 });
    m_Sprite[4] = GECore::SubTexture2D::Create(spriteSheet, { 4, 0 }, { 128, 128 });
    m_Sprite[5] = GECore::SubTexture2D::Create(spriteSheet, { 5, 0 }, { 128, 128 });
}


void TestLayer::update(GECore::Time dt) {
  // update
  m_CameraController->update(dt);

  // render
  GECore::Renderer2D::ResetStatistics();
  {
    GECore::RenderCommand::ClearColor(GECore::COLOR::WHITE);
  }

  {
    GECore::Renderer2D::BeginScene(m_CameraController->getCamera());
    static double acc;
    acc += dt.getMilliseconds();
    static int i;
    if (100 <= acc) {
      i = (i + 1) % 6;
      acc = 0;
    }
    GECore::Renderer2D::DrawQuad({ 0.f, 0.f }, { 1.f, 1.f }, m_Sprite[i]);
    GECore::Renderer2D::EndScene();
  }
}


void TestLayer::ImGUIRender() {
  ImGui::Begin("Settings");
  auto stats = GECore::Renderer2D::GetStatistics();
  ImGui::Text("Renderer2D Stats:");
  ImGui::Text("Draw Calls: %d",    stats.DrawCalls);
  ImGui::Text("Quads: %d",         stats.Quads);
  ImGui::Text("Vertcies: %d",      stats.Vertcies);
  ImGui::Text("Indecies: %d",      stats.Indecies);
  ImGui::End();
}


void TestLayer::onWindowResize(GECore::window_resize_e &e) {
    m_CameraController->onWindowResize(e);
}


void TestLayer::onMouseScroll(GECore::mouse_scroll_e &e) {
    m_CameraController->onMouseScroll(e);
}
