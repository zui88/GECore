//
// Created by zui on 2/12/23.
//

#include "GECore/Core/OrtographicCameraController.h"
#include "GECore/Core/Input/Input.h"
#include "GECore/Renderer/OrtographicCamera.h"

namespace GECore {

    void OrtographicCameraController::update(Time dt) {
        m_TranslationSpeed = m_ZoomLevel;
        bool isCameraSet { false };

        if (Input::IsKeyPressed(GE_KEY_D)) {
            m_Camera->setPosition(m_Camera->getPosition() + glm::vec3{m_TranslationSpeed * dt, 0.0f, 0.0f});
            isCameraSet = true;
        }
        else if (Input::IsKeyPressed(GE_KEY_A)) {
            m_Camera->setPosition(m_Camera->getPosition() + glm::vec3{Time::Neg(m_TranslationSpeed * dt), 0.0f, 0.0f});
            isCameraSet = true;
        }

        if (Input::IsKeyPressed(GE_KEY_W)) {
            m_Camera->setPosition(m_Camera->getPosition() + glm::vec3{0.0f, m_TranslationSpeed * dt, 0.0f});
            isCameraSet = true;
        }
        else if (Input::IsKeyPressed(GE_KEY_S)) {
            m_Camera->setPosition(m_Camera->getPosition() + glm::vec3{0.0f, Time::Neg(m_TranslationSpeed * dt), 0.0f});
            isCameraSet = true;
        }

        if (Input::IsKeyPressed(GE_KEY_E)) {
            m_Camera->setRotation(m_Camera->getRotation() + m_RotationSpeed * dt);
            isCameraSet = true;
        } else if (Input::IsKeyPressed(GE_KEY_Q)) {
            m_Camera->setRotation(m_Camera->getRotation() + Time::Neg(m_RotationSpeed * dt));
            isCameraSet = true;
        }

        if(isCameraSet) m_Camera->update();
    }

    Ref<OrtographicCamera> const &OrtographicCameraController::getCamera() const {
        return m_Camera;
    }

    Scope<OrtographicCameraController> OrtographicCameraController::Create(float aspectRatio) {
        Scope<OrtographicCameraController> cameraController{new OrtographicCameraController{}};
        cameraController->m_AspectRation = aspectRatio;
        auto camera = OrtographicCamera::Create(-cameraController->m_ZoomLevel * aspectRatio, cameraController->m_ZoomLevel * aspectRatio, -cameraController->m_ZoomLevel * aspectRatio, cameraController->m_ZoomLevel * aspectRatio);
        cameraController->m_Camera = camera;
        return cameraController;
    }

    void OrtographicCameraController::onWindowResize(window_resize_e const& e) {
        m_AspectRation = static_cast<float>(e.width) / static_cast<float>(e.height);
        m_Camera->setProjection(-m_ZoomLevel * m_AspectRation, m_ZoomLevel * m_AspectRation, -m_ZoomLevel, m_ZoomLevel);
        m_Camera->update();
    }

    void OrtographicCameraController::onMouseScroll(const mouse_scroll_e &e) {
        if (e.yoffset == -1) {
            m_ZoomLevel *= 1.1f;
        } else if (e.yoffset == 1) {
            m_ZoomLevel *= 0.9f;
        }
        m_Camera->setProjection(-m_ZoomLevel * m_AspectRation, m_ZoomLevel * m_AspectRation, -m_ZoomLevel, m_ZoomLevel);
        m_Camera->update();
    }
}