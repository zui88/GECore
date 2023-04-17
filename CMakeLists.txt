cmake_minimum_required(VERSION 3.12...3.25)
project("Graphic Engine Core Library")

find_package(OpenGL REQUIRED)

# Add dependencies
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/entt)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/zui)

# Add source files
set(CORE
        src/Core/Input/GLFWInput.cpp
        src/Core/Input/Input.cpp

        src/Core/Application.cpp
        src/Core/Layer.cpp
        src/Core/Logger.cpp
        src/Core/Window.cpp
        src/Core/Time.cpp
        src/Core/OrtographicCameraController.cpp
        )

set(RENDER
        src/Renderer/Buffer.cpp
        src/Renderer/Shader.cpp
        src/Platform/OpenGL/Context.cpp
        src/Renderer/Renderer.cpp
        src/Renderer/Texture2D.cpp
        src/Renderer/SubTexture2D.cpp
        src/Renderer/OrtographicCamera.cpp
        src/Renderer/RenderCommand.cpp
        src/Renderer/IndexBuffer.cpp
        src/Renderer/VertexArray.cpp
        src/Renderer/Renderer2D.cpp
        src/Renderer/FrameBuffer.cpp
      )

set(PRIMITIVES
  src/Primitives/Quad.cpp
)

add_library(GECore
        ${CORE}
        ${RENDER}
        ${PRIMITIVES}
      )

target_include_directories(GECore
  PRIVATE vendor/stb
)

target_include_directories(GECore
        PRIVATE vendor/stb
        )

target_compile_features(GECore
        PUBLIC cxx_std_17
        )

target_include_directories(GECore
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        )

target_link_libraries(GECore
        imgui::imgui
        glad::glad
        glfw
        OpenGL::GL
        spdlog::spdlog
        glm::glm
        EnTT::EnTT
        zui::zui
        )

# tests
# add_subdirectory(tests/BatchRendering)
add_subdirectory(tests/Triangle)
add_subdirectory(tests/2DRenderer)

