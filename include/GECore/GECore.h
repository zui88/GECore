#pragma once

/* Core part */
#include "GECore/Core/Core.h"
#include "GECore/Core/Logger.h"
#include "GECore/Core/Application.h"
#include "GECore/Core/Color.h"
#include "GECore/Core/Time.h"
#include "GECore/Core/OrtographicCameraController.h"

/* Events */
#include "GECore/Core/Events/Close.h"
#include "GECore/Core/Events/CursorMove.h"
#include "GECore/Core/Events/KeyboardPress.h"
#include "GECore/Core/Events/MousePress.h"
#include "GECore/Core/Events/MouseScroll.h"
#include "GECore/Core/Events/WindowResize.h"

/* Layer */
#include "GECore/Core/Layer.h"

/* Input */
#include "GECore/Core/Input/Input.h"
#include "GECore/Core/Input/Keycode.h"

/* Render */
/* temporary till renderer is defined and implementet */
#include "GECore/Renderer/Renderer.h"
#include "GECore/Renderer/Renderer2D.h"
/* ultimately render internals */
#include "GECore/Renderer/Shader.h"
#include "GECore/Renderer/Buffer.h"
#include "GECore/Renderer/IndexBuffer.h"
#include "GECore/Renderer/VertexArray.h"
#include "GECore/Renderer/Texture2D.h"
#include "GECore/Renderer/SubTexture2D.h"
#include "GECore/Renderer/RenderCommand.h"
#include "GECore/Renderer/FrameBuffer.h"
