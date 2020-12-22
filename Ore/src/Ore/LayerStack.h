#pragma once

#include "Ore/Core.h"
#include "Layer.h"
#include <vector>

namespace Ore {
	class API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return p_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return p_Layers.end(); }

	protected:
		std::vector<Layer*> p_Layers;
		unsigned int p_LayerInsertIndex = 0;
	};
}