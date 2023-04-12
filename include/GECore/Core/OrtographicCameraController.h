//
// Created by zui on 2/12/23.
//

#ifndef OGLGE_ORTOGRAPHICCAMERACONTROLLER_H
#define OGLGE_ORTOGRAPHICCAMERACONTROLLER_H

#include "GECore/Core/Core.h"
#include "GECore/Core/Time.h"

#include "GECore/Core/Events/WindowResize.h"
#include "GECore/Core/Events/MouseScroll.h"

namespace GECore {
    class OrtographicCamera;

    class OrtographicCameraController {
    public:
        void update(Time dt);

        [[nodiscard]] Ref<OrtographicCamera> const& getCamera() const;

        static Scope<OrtographicCameraController> Create(float aspectRatio);

        void onWindowResize(window_resize_e const& e);

        void onMouseScroll(mouse_scroll_e const& e);

    private:
        Ref<OrtographicCamera> m_Camera;
        float m_AspectRation;
        float m_ZoomLevel { 2.0f };
        Time m_TranslationSpeed {1.5 };
        Time m_RotationSpeed {1.0 };
    };
}
#endif //OGLGE_ORTOGRAPHICCAMERACONTROLLER_H
