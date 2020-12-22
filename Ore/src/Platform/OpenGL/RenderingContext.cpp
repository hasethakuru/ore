#include "opch.h"
#include "RenderingContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Ore {
	RenderingContext::RenderingContext(GLFWwindow* window)
		: p_window(window)
	{
		ORE_CORE_ASSERT(window, "Window is null");
	}

	void RenderingContext::Init()
	{
		glfwMakeContextCurrent(p_window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ORE_CORE_ASSERT(status, "Failed to intialize GLAD");
	}
	void RenderingContext::SwapBuffers()
	{
		glfwSwapBuffers(p_window);
	}
}