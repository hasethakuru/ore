#include "opch.h"
#include "VertexArray.h"
#include "RendererAPI.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ore {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::RenderAPI::None:    ORE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::RenderAPI::OpenGL:  return new OpenGLVertexArray();
		}

		ORE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}