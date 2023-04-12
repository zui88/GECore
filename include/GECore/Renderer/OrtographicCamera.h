//
// Created by zui on 2/2/23.
//

#ifndef OGLGE_ORTOGRAPHICCAMERA_H
#define OGLGE_ORTOGRAPHICCAMERA_H

#include "GECore/Core/Time.h"

#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext.hpp" //ortho

#include "GECore/Core/Core.h"

namespace GECore {

    class OrtographicCamera;

    typedef Ref<OrtographicCamera> RefOrtographicCamera;

    class OrtographicCamera {
    public:
        OrtographicCamera(glm::mat4 const& ortho);
        OrtographicCamera(float left, float right, float bottom, float top);

        OrtographicCamera() {}

        [[nodiscard]] glm::mat4 const& getViewProjectionMatrix() const;

        [[nodiscard]] glm::mat4 const& getProjectionMatrix() const;
        [[nodiscard]] glm::mat4& getProjectionMatrix();

        [[nodiscard]] glm::mat4 const& getViewMatrix() const;
        [[nodiscard]] glm::mat4& getViewMatrix();

        void setPosition(glm::vec3 const& pos);
        [[nodiscard]] glm::vec3 getPosition() const;

        void setProjection(float left, float right, float bottom, float top);

        void update();

        void setRotation(float degree);
        [[nodiscard]] float getRotation() const;

        static RefOrtographicCamera Create(float left, float right, float bottom, float top);

    private:
        glm::mat4 m_View;
        glm::mat4 m_Projection;
        glm::mat4 m_VP;

        glm::vec3 m_Position;
        float m_Rotation;
    };

} // GECore

#endif //OGLGE_ORTOGRAPHICCAMERA_H
