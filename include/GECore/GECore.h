#pragma once

/* Core part */
#include "Core/Logger.h"
#include "Core/Application.h"
#include "GECore/Core/Color.h"
#include "GECore/Core/Time.h"
#include "GECore/Core/OrtographicCameraController.h"

/* Events */
#include "Core/Events/Close.h"
#include "Core/Events/CursorMove.h"
#include "Core/Events/KeyboardPress.h"
#include "Core/Events/MousePress.h"
#include "Core/Events/MouseScroll.h"
#include "Core/Events/WindowResize.h"

/* Layer */
#include "Core/Layer.h"

/* Input */
#include "Core/Input/Input.h"
#include "Core/Input/Keycode.h"

/* Render */
/* temporary till renderer is defined and implementet */
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
/* ultimately render internals */
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Texture2D.h"
#include "Renderer/SubTexture2D.h"
#include "Renderer/RenderCommand.h"
