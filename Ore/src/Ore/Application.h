#pragma once
#include "Core.h"
#include "Ore/Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "LayerStack.h"
#include "Window.h"

namespace Ore {
	class API App {
	public:
		App();
		virtual ~App();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> p_Window;
		bool p_Running = true;
		LayerStack p_layerStack;
	};

	App* CreateApplication();
}