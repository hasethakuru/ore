#pragma once

#include "Ore/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Ore {
	class RenderingContext : public GraphicsContext
	{
	public:
		RenderingContext(GLFWwindow* window);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* p_window;
	};
}