#pragma once

#include <glm/glm.hpp>

namespace eogl {
#define EOGL_EVENT_COUNT 7
	enum eventType {
		EOGL_UNKNOWN_EVENT = 0,
		EOGL_KEY_EVENT= 1 ,
		EOGL_MOUSE_POS_EVENT=2 ,
		EOGL_MOUSE_BUTTON_EVENT=3,
		EOGL_MOUSE_SCROLL_EVENT = 4,
		EOGL_WINDOW_RESIZE_EVENT = 5,
		EOGL_CHAR_EVENT = 6,
		EOGL_WINDOW_POS_EVENT = 7,
		EOGL_MONITOR_EVENT = 8
		
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
	class MonitorEvent : public Event {
		int event;
		MonitorEvent(int event);
	};
	class WindowPosEvent : public Event {
		glm::vec2 pos;
		WindowPosEvent(glm::vec2 pos);
	};

}