#include "Ore.h"

class SandboxLayer : public Ore::Layer {
public:
	SandboxLayer()
		: Layer("Sandbox")
	{
	}

	void OnUpdate() override
	{
		ORE_INFO("Updated Sandbox Layer");
	}

	void OnEvent(Ore::Event& event) override
	{
		ORE_TRACE("{0}", event);
	}
};

class Sandbox : public Ore::App {
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
		PushOverlay(new Ore::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Ore::App* Ore::CreateApplication()
{
	return new Sandbox();
}