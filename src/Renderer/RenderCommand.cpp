//
// Created by zui on 2/6/23.
//

#include "GECore/Renderer/RenderCommand.h"

#include "glad/glad.h"
#include "glm/vec3.hpp"

#include "GECore/Core/Logger.h"
#include <cstdint>

namespace GECore {

    static inline glm::vec3 ColorLookup(COLOR color) {
        switch (color) {
            case COLOR::WHITE:
                return {1.0f, 1.0f, 1.0f};
            case COLOR::BLACK:
                return {0.0f, 0.0f, 0.0f};
            default:
                return {0.0f, 0.0f, 0.0f};
        }

    }

    void RenderCommand::ClearColor(COLOR color) {
        glm::vec3 color_ = ColorLookup(color);
        glClearColor(color_.r, color_.g, color_.b, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void RenderCommand::Clear() {}


    void RenderCommand::StartUp() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void RenderCommand::DrawIndexed(const Ref<VertexArray> &vertexArray) {
	vertexArray->bind();
	auto ib { vertexArray->getIndexBuffer() };
        glMultiDrawElementsBaseVertex(GL_TRIANGLES,
				      ib->getIndicesCountsArray(),
				      ib->getIndexType(),
				      ib->getOffsetArray(),
				      ib->getGeometryCount(),
				      ib->getBaseVertexArray());
	GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            GE_CORE_ERROR("RenderCommand @ OpenGL Error: {}", err);
        }
    }

} // namespace GECore
