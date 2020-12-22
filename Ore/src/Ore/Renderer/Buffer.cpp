#include "opch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Ore {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::RenderAPI::None:    ORE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::RenderAPI::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		}

		ORE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::RenderAPI::None:    ORE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::RenderAPI::OpenGL:  return new OpenGLIndexBuffer(indices, size);
		}

		ORE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}