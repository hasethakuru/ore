#pragma once

namespace Ore
{
	class Timestep {
	public:
		Timestep(float time = 0.0f)
			: p_Time(time)
		{

		}

		operator float() const { return p_Time; }

		float GetSeconds() const { return p_Time; }
		float GetMilliseconds() const { return p_Time * 1000.0f; }
	private:
		float p_Time;
	};
}