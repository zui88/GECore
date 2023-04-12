#pragma once

#include "GECore/GECore.h"

using namespace GECore;

struct Position {
    float x, y, z;
};
struct TextureCoords {
    float u, v;
};

struct Color {
    float r, g, b, a;
};

struct TexID {
    float slot;
};

struct Vertex {
    Position p;
    TextureCoords t;
    Color c;
    TexID tid;
};

struct Rectangle {
    Vertex a, b, c, d;
};

struct MyLayer : public Layer {

    void attach() override {
        // camera
        m_CameraController = OrtographicCameraController::Create(16.f / 10.f);

        // material
        // data
        Rectangle Rect[2]{};
        Rect[0].a.p = {-0.5f, -0.5f, 0.0f};
        Rect[0].a.t = {0.0f, 0.0f};
        Rect[0].a.tid = {1.0f };

        Rect[0].b.p = {0.5f, -0.5f, 0.0f};
        Rect[0].b.t = {1.0f, 0.0f};
        Rect[0].b.tid = {1.0f };

        Rect[0].c.p = {0.5f, 0.5f, 0.0f};
        Rect[0].c.t = {1.0f, 1.0f};
        Rect[0].c.tid = {1.0f };

        Rect[0].d.p = {-0.5f, 0.5f, 0.0f};
        Rect[0].d.t = {0.0f, 1.0f};
        Rect[0].d.tid = {1.0f };

        Rect[1].a.p = {1.5f, -0.5f, 0.0f};
        Rect[1].a.t = {0.0f, 0.0f};
        Rect[1].a.tid = {2.0f };

        Rect[1].b.p = {2.5f, -0.5f, 0.0f};
        Rect[1].b.t = {1.0f, 0.0f};
        Rect[1].b.tid = {2.0f };

        Rect[1].c.p = {2.5f, 0.5f, 0.0f};
        Rect[1].c.t = {1.0f, 1.0f};
        Rect[1].c.tid = {2.0f };

        Rect[1].d.p = {1.5f, 0.5f, 0.0f};
        Rect[1].d.t = {0.0f, 1.0f};
        Rect[1].d.tid = {2.0f };

        // buffer with layout
        m_VAO = VertexArray::Create();
        auto buffer = Buffer::Create(&Rect, sizeof(Rect));
        buffer->setLayout({
            {"a_Pos", ShaderDataType::Float3},
            {"a_TexPos", ShaderDataType::Float2},
            {"a_Color", ShaderDataType::Float4},
            {"a_TexID", ShaderDataType::Float}});
        m_VAO->add(buffer);

        // indicies -> save vertices
        uint32_t indicies[] = {
                0, 1, 2,
                2, 3, 0,

               4 ,5, 6,
               6, 7, 4
        };
        auto indexBuffer = IndexBuffer::Create(indicies);
        m_VAO->add(indexBuffer);

        m_Shader = Shader::Create("Batch Shader", "assets/shader.glsl.vert", "assets/shader.glsl.frag");

        m_Shader->bind();
        int sampler[] { 0, 1, 2 };
        m_Shader->setIntArry("u_Textures", sampler);

        m_TexSun = Texture2D::Create("sun.png", 1);
        m_TexSun->bind();
        m_TexSailorMoon = Texture2D::Create("sailor-moon.png", 2);
        m_TexSailorMoon->bind();
    }

    void update(Time dt) override {
        m_CameraController->update(dt);

        RenderCommand::ClearColor(COLOR::WHITE);
        Renderer::BeginScene(m_CameraController->getCamera());
        Renderer::Submit(m_VAO, m_Shader, m_Model);
        Renderer::EndScene();
    }

//    void ImGUIRender() override {
//        ImGui::Begin("Hello world");
//        ImGui::End();
//    }

    void onWindowResize(window_resize_e &e) override {
        m_CameraController->onWindowResize(e);
    }

    void onMouseScroll(mouse_scroll_e &e) override {
        m_CameraController->onMouseScroll(e);
    }

    RefVertexArray m_VAO;
    RefTexture m_TexSun, m_TexSailorMoon;
    RefShader m_Shader;
    Scope<OrtographicCameraController> m_CameraController;

    glm::vec3 m_Scale { 1.0f, 1.0f, 1.0f };
    glm::mat4 m_Model{ 1.0 };
};
