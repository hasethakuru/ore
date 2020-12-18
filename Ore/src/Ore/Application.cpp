#include "opch.h"
#include "Application.h"
#include "Ore/Events/ApplicationEvent.h"
#include "Log.h"
#include "glad/glad.h"
#include "Input.h"

namespace Ore {
#define BIND_EVENT_FN(e) std::bind(&App::e, this, std::placeholders::_1)

	App* App::p_Instance = nullptr;

	App::App()
	{
		ORE_CORE_ASSERT(!p_Instance, "Application instance already exists");
		p_Instance = this;
		p_Window = std::unique_ptr<Window>(Window::Create());
		p_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	App::~App()
	{
	}

	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		ORE_CORE_TRACE("{0}", e);

		for (auto it = p_layerStack.end(); it != p_layerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}


	void App::Run()
	{
		while (p_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : p_layerStack)
				layer->OnUpdate();

			auto [x, y] = Input::GetMousePosition();
			ORE_CORE_TRACE("{0}, {1}", x, y);
			p_Window->OnUpdate();
		}
	}

	void App::PushLayer(Layer* layer)
	{
		p_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void App::PushOverlay(Layer* layer)
	{
		p_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		p_Running = false;
		return true;
	}
}