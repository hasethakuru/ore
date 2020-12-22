#pragma once

#include "Ore/Log.h"
#include "Ore/Window.h"
#include <GLFW/glfw3.h>
#include "Ore/Renderer/GraphicsContext.h"
#include "Platform/OpenGL/RenderingContext.h"

namespace Ore {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return p_Data.Width; }
		inline unsigned int GetHeight() const override { return p_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { p_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return p_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* p_Window;
		RenderingContext* p_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData p_Data;
	};

}