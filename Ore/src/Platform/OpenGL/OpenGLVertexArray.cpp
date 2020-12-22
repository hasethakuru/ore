#include "opch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Ore {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Ore::ShaderDataType::Float:    return GL_FLOAT;
			case Ore::ShaderDataType::Float2:   return GL_FLOAT;
			case Ore::ShaderDataType::Float3:   return GL_FLOAT;
			case Ore::ShaderDataType::Float4:   return GL_FLOAT;
			case Ore::ShaderDataType::Mat3:     return GL_FLOAT;
			case Ore::ShaderDataType::Mat4:     return GL_FLOAT;
			case Ore::ShaderDataType::Int:      return GL_INT;
			case Ore::ShaderDataType::Int2:     return GL_INT;
			case Ore::ShaderDataType::Int3:     return GL_INT;
			case Ore::ShaderDataType::Int4:     return GL_INT;
			case Ore::ShaderDataType::Bool:     return GL_BOOL;
		}

		ORE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &p_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &p_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(p_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		ORE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(p_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		p_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(p_RendererID);
		indexBuffer->Bind();

		p_IndexBuffer = indexBuffer;
	}

}