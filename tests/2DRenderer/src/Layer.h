#pragma once

#include "GECore/GECore.h"
#include "GECore/Renderer/Texture2D.h"

struct TestLayer : public GECore::Layer {

    void attach() override;

    void update(GECore::Time dt) override;

    void ImGUIRender() override;

    void onWindowResize(GECore::window_resize_e &e) override;

    void onMouseScroll(GECore::mouse_scroll_e &e) override;

    GECore::Scope<GECore::OrtographicCameraController> m_CameraController;
    GECore::Ref<GECore::Texture2D> m_Texture[2];
    GECore::Ref<GECore::SubTexture2D> m_Sprite[6];
};
