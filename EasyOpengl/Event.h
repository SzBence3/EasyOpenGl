#pragma once

#include <glm/glm.hpp>

namespace eogl {
	enum eventType {
		EOGL_KEY_EVENT,
		EOGL_MOUSE_POS_EVENT,
		EOGL_MOUSE_BUTTON_EVENT,
		EOGL_MOUSE_SCROLL_EVENT,
		EOGL_WINDOW_RESIZE_EVENT,
		EOGL_CHAR_EVENT,
		EOGL_MONITOR_EVENT
		
	};
	class Event {
	public:
		int type;
	};

	class KeyEvent : public Event {
	public:
		int key;
		int scancode;
		int action;
		int mods;
		KeyEvent(int key, int scancode, int action, int mods);
	};
	class MousePosEvent : public Event {
	public:
		glm::vec2 pos;
		MousePosEvent(glm::vec2 pos);
	};
	class MouseButtonEvent : public Event {
	public:
		int button;
		int action;
		int mods;
		MouseButtonEvent(int button, int action, int mods);
	};
	class MouseScrollEvent : public Event {
	public:
		glm::vec2 offset;
		MouseScrollEvent(glm::vec2 offset);
	};
	class WindowResizeEvent : public Event {
	public:
		glm::vec2 size;
		WindowResizeEvent(glm::vec2 size);
	};
	class CharEvent : public Event {
	public:
		unsigned int codepoint;
		CharEvent(unsigned int codepoint);
	};


}