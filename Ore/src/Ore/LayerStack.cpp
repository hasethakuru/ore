#include "opch.h"
#include "LayerStack.h"

namespace Ore {
	LayerStack::LayerStack() {
		
	}
	
	LayerStack::~LayerStack() {
		for (Layer* layer : p_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer) {
		p_Layers.emplace(p_Layers.begin() + p_LayerInsertIndex, layer);
		p_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		p_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(p_Layers.begin(), p_Layers.end(), layer);
		if (it != p_Layers.end()) {
			p_Layers.erase(it);
			p_LayerInsertIndex--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(p_Layers.begin(), p_Layers.end(), overlay);
		if (it != p_Layers.end())
			p_Layers.erase(it);
	}
}