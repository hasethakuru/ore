#include "opch.h"
#include "WindowsWindow.h"
#include "WinInput.h"
#include "Ore/Application.h"
#include <GLFW/glfw3.h>

namespace Ore
{

	Input* Input::p_Instance = new WinInput();
	bool WinInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WinInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WinInput::GetMousePositionImpl() {
		auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

	float WinInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return (float)x;
	}

	float WinInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return (float)y;
	}
}