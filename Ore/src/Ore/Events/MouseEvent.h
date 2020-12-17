#pragma once

#include "Event.h"

namespace Ore {
	class API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: p_MouseX(x), p_MouseY(y) {}

		inline float GetX() const { return p_MouseX; }
		inline float GetY() const {return p_MouseY;}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << p_MouseX << ", " << p_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float p_MouseX, p_MouseY;
	};

	class API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float offsetX, float offsetY)
			: p_offsetX(offsetX), p_offsetY(offsetY) {}

		inline float GetOffsetX() const { return p_offsetX; }
		inline float GetOffsetY() const { return p_offsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetOffsetX() << ", " << GetOffsetY();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float p_offsetX, p_offsetY;
	};

	class API MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const {
			return p_button;
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			: p_button(button) {}
		int p_button;
	};

	class API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << p_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << p_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}