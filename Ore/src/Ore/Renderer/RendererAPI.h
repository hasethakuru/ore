#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Ore {
	class RendererAPI {
	public:
		enum class RenderAPI {
			None  = 0,
			OpenGL = 1
		};
	public:
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		inline static RenderAPI GetAPI() { return s_API; }
	private:
		static RenderAPI s_API;
	};
}