#pragma once

#include "Event.h"

namespace Ore {
	class API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const {
			return p_KeyCode;
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
	protected:
		KeyEvent(int keycode)
			: p_KeyCode(keycode) {}

		int p_KeyCode;
	};

	class API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int count)
			: KeyEvent(keycode), p_count(count) {}

		inline int GetCount() const {
			return p_count;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << p_KeyCode << " (" << p_count << " counted)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int p_count;
	};

	class API KeyReleasedEvent: public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << p_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}