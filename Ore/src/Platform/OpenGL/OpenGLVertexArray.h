#pragma once

#include "Ore/Renderer/VertexArray.h"

namespace Ore {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return p_VertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return p_IndexBuffer; }
	private:
		uint32_t p_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> p_VertexBuffers;
		std::shared_ptr<IndexBuffer> p_IndexBuffer;
	};

}