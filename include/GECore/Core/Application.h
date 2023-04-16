#pragma once

#include <string>

#include "Events/Close.h"
#include "Events/CursorMove.h"
#include "Events/KeyboardPress.h"
#include "Events/MousePress.h"
#include "Events/WindowResize.h"
#include "Events/MouseScroll.h"

#include "GECore/Core/Time.h"

#include "BasicLayer.h"
#include "../Renderer/Shader.h"

#include <zui/zui.h>

struct GLFWwindow;
typedef GLFWwindow *NativWindow;

namespace GECore {


    class Window;


    class Application {
        typedef std::unique_ptr<Window> window_t;


        typedef zui::layer_stack<BasicLayer> layer_stack_t;


      public:
        typedef Application *application_t;


        struct Properties {
	  std::string AssetPath;
        };

 
        Application();


        Application(std::string_view applicationName);


        Application(int width, int height, std::string_view applicationName);


        // because virtual destructor
        virtual ~Application();


        Application(const Application &) = delete;


        Application &operator=(const Application &) = delete;


        Application(Application &&) = delete;


        Application &operator=(Application &&) = delete;


        void run();


        virtual void startup() {}


        virtual void shutdown() {}


        template<typename Resource, typename... Args>
        layer_whandle pushLayer(Args &&...args);


        template<typename Resource, typename... Args>
        layer_whandle pushOverlay(Args &&...args);


        Layer_H popLayer(Layer_H const &layer);


        Layer_H popOverlay(Layer_H const &layer);


        static application_t GetApplication();


        // ToDo: more than one window will be supported in future
        NativWindow getNativWindow();


        int getWidth();


        int getHeight();

      
        static Properties const &GetProperties();


      private:
        void updateLayer(Time time);


        void windowCloseEvent();


        void mousePressEvent(mouse_press_e &);


        void mouseScrollEvent(mouse_scroll_e &);


        void cursorMoveEvent(cursor_move_e &);


        void keyboardPressEvent(keyboard_press_e &);


        void windowResizeEvent(window_resize_e &);


        void open();


        void ImGUIRender();


        ////////////////////////////////////////////////////////////////
        //
        // Fields
        //
        ////////////////////////////////////////////////////////////////
      private:
        static Properties s_Properties;

	
	static inline application_t s_Application{ nullptr };
        
	
	layer_stack_t m_LayerStack;
        
	
	window_t m_Window;
        
	
	bool m_IsRunning{ true };
        
	
	Time::type m_LastTimeStep;
    };


    template<typename Resource, typename... Args>
    layer_whandle Application::pushLayer(Args &&...args) {
        auto *layer = new Resource{std::forward<Args>(args)...};
        layer->attach();
        // auto Layer_H =
        // std::make_shared<Resource>(std::forward<Args>(args)...);
        // Layer_H.reset(layer);
        auto layer_handle = std::shared_ptr<Resource>(layer);
        return m_LayerStack.emplace_layer(layer_handle);
    }


    template<typename Resource, typename... Args>
    layer_whandle Application::pushOverlay(Args &&...args) {
        auto *layer = new Resource{std::forward<Args>(args)...};
        layer->attach();
        auto layer_handle = std::shared_ptr<Resource>(layer);
        return m_LayerStack.emplace_overlay(layer_handle);
    }


  // To be defined in the client
    std::unique_ptr<Application> CreateApplication();


} // namespace GECore
