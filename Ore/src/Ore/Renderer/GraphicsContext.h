#pragma once
#include "Ore/Core.h"

namespace Ore {
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}