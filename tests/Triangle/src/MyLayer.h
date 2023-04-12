#pragma once

#include "GECore/GECore.h"

using namespace GECore;

struct MyLayer : public Layer {

    void attach() override {
        m_Camera = OrtographicCamera::Create(-2.0f, 2.0f, -1.5f, 1.5f);

        float Rect[] =
                {-0.5f, -0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f,
                 0.5f, 0.5f, 0.0f,
                 -0.5f, 0.5f, 0.0f};

        m_VAO = VertexArray::Create();
	m_Buffer = Buffer::Create(Rect);
        m_Buffer->setLayout({
                                    {"a_Pos", ShaderDataType::Float3}
                            });
        m_VAO->add(m_Buffer);
        uint32_t indicies[] = {
                0, 1, 2,
                2, 3, 0
        };
        m_IndexBuffer = IndexBuffer::Create(indicies);
        m_VAO->add(m_IndexBuffer);
        m_Shader = Shader::Create("VertexFragment", "shader.glsl.vert", "white.glsl.frag");
    }

    void update(Time dt) override {
        RenderCommand::ClearColor();
        Renderer::BeginScene(m_Camera);
        Renderer::Submit(m_VAO, m_Shader, m_Model);
        Renderer::EndScene();
    }

    RefIndexBuffer m_IndexBuffer;
    RefVertexArray m_VAO;
    RefBuffer m_Buffer;
    RefShader m_Shader;
    RefOrtographicCamera m_Camera;

    glm::mat4 m_Model{ 1.0 };
};
