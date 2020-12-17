#include "opch.h"
#include "WindowsWindow.h"
#include "Ore/Events/ApplicationEvent.h"
#include "Ore/Events/MouseEvent.h"
#include "Ore/Events/KeyEvent.h"

namespace Ore {
	static bool GLFW_INIT = false;
	static void GLFWErrorCallback(int error, const char* description) {
		ORE_CORE_ERROR("GLFW ERROR ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {}

	void WindowsWindow::Init(const WindowProps& props)
	{
		p_Data.Title = props.Title;
		p_Data.Width = props.Width;
		p_Data.Height = props.Height;

		ORE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!GLFW_INIT) {
			int success = glfwInit();
			ORE_CORE_ASSERT(success,  "Could not intialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			GLFW_INIT = true;
		}

		p_Window = glfwCreateWindow((int)props.Width, (int)props.Height, p_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(p_Window);
		glfwSetWindowUserPointer(p_Window, &p_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(p_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(p_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(p_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
				case GLFW_REPEAT: 
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
			}
		});

		glfwSetMouseButtonCallback(p_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
			
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(p_Window, [](GLFWwindow* window, double OffsetX, double OffsetY) 
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)OffsetX, (float)OffsetY);
				data.EventCallback(event);
		});

		glfwSetCursorPosCallback(p_Window, [](GLFWwindow* window, double posX, double posY)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)posX, (float)posY);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(p_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(p_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		p_Data.VSync = true;
	}

	bool WindowsWindow::IsVSync() const
	{
		return p_Data.VSync;
	}
}