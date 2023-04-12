//
// Created by zui on 2/2/23.
//

#include "GECore/Renderer/OrtographicCamera.h"

namespace GECore {

    OrtographicCamera::OrtographicCamera(glm::mat4 const& ortho)
    : m_Position{ 0.0f, 0.0f, 0.0f }, m_Rotation { 0.0f }, m_View { 1.0f }, m_Projection { ortho }
    {
        m_VP = m_Projection * m_View;
    }

    OrtographicCamera::OrtographicCamera(float left, float right, float bottom, float top)
            : OrtographicCamera{ glm::ortho( left, right, bottom, top, -1.f, 1.f ) }
    {

    }

    glm::mat4 const& OrtographicCamera::getViewProjectionMatrix() const {
        return m_VP;
    }

    RefOrtographicCamera OrtographicCamera::Create(float left, float right, float bottom, float top) {
        return new OrtographicCamera{ left, right, bottom, top };
    }

    void OrtographicCamera::setPosition(const glm::vec3 &pos) {
        m_Position = pos;
    }

    glm::vec3 OrtographicCamera::getPosition() const {
        return m_Position;
    }

    void OrtographicCamera::setRotation(float degree) {
        m_Rotation = degree;
    }

    float OrtographicCamera::getRotation() const {
        return m_Rotation;
    }

    glm::mat4 const &OrtographicCamera::getProjectionMatrix() const {
        return m_Projection;
    }

    glm::mat4 const &OrtographicCamera::getViewMatrix() const {
        return m_View;
    }

    void OrtographicCamera::update() {
        m_View = glm::inverse(glm::translate(glm::mat4 {1.0f}, m_Position) *
                              glm::rotate(glm::mat4 { 1.0f }, m_Rotation, glm::vec3{0.0f, 0.0f, 1.0f}));
        m_VP = m_Projection * m_View;
    }

    glm::mat4 &OrtographicCamera::getProjectionMatrix() {
        return m_Projection;
    }

    glm::mat4 &OrtographicCamera::getViewMatrix() {
        return m_View;
    }

    void OrtographicCamera::setProjection(float left, float right, float bottom, float top) {
        m_Projection = glm::ortho(left, right, bottom, top,  -1.f, 1.f);
    }

} // GECore
