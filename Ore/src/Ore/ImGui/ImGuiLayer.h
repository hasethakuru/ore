#pragma once

#include "Ore/Layer.h"
#include "Ore/Events/ApplicationEvent.h"
#include "Ore/Events/KeyEvent.h"
#include "Ore/Events/MouseEvent.h"

namespace Ore {
	class API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	private:
		float p_Time = 0.0f;
	};
}