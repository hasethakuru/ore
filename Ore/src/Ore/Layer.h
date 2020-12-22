#pragma once

#include "Ore/Core.h"
#include "Ore/Events/Event.h"
#include "Ore/Core/Timestep.h"
#include <iostream>

namespace Ore {
	class API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate (Timestep deltaTime) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName()  const { return p_DebugName; }
	protected:
		std::string p_DebugName;
	};
}