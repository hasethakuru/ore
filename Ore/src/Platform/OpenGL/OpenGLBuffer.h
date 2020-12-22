#pragma once

#include "Ore/Renderer/Buffer.h"
#include <glad/glad.h>

namespace Ore {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetLayout(const BufferLayout& layout) override { p_Layout = layout; };
		virtual const BufferLayout& GetLayout() const override {return p_Layout;};
	private:
		uint32_t p_RendererID;
		BufferLayout p_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer 
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;
		virtual uint32_t GetCount() const { return p_Count; }
	private:
		uint32_t p_RendererID;
		uint32_t p_Count;
	};
}