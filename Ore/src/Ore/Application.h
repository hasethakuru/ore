#pragma once
#include "Core.h"
#include "Ore/Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "LayerStack.h"
#include "Window.h"
#include "ImGui/ImGuiLayer.h"
#include "Core/Timestep.h"

namespace Ore {
	class API App {
	public:
		App();
		virtual ~App();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);


		inline static App& Get() { return *p_Instance; }
		inline Window& GetWindow() { return *p_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> p_Window;
		ImGuiLayer* p_ImGuiLayer;
		bool p_Running = true;
		LayerStack p_layerStack;
		float p_latestFrame = 0.0f;
	private:
		static App* p_Instance;
	};

	App* CreateApplication();
}