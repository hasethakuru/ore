#include "opch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ore {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRenderAPI;
}