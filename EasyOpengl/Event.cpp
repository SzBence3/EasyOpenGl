#include"Event.h"

namespace eogl {
	KeyEvent::KeyEvent(int key, int scancode, int action, int mods) {
		this->key = key;
		this->scancode = scancode;
		this->action = action;
		this->mods = mods;
		type = EOGL_KEY_EVENT;
	}
	MousePosEvent::MousePosEvent(glm::vec2 pos) {
		this->pos = pos;
		type = EOGL_MOUSE_POS_EVENT;
	}
	MouseButtonEvent::MouseButtonEvent(int button, int action, int mods) {
		this->button = button;
		this->action = action;
		this->mods = mods;
		type = EOGL_MOUSE_BUTTON_EVENT;
	}
	MouseScrollEvent::MouseScrollEvent(glm::vec2 offset) {
		this->offset = offset;
		type = EOGL_MOUSE_SCROLL_EVENT;
	}
	WindowResizeEvent::WindowResizeEvent(glm::vec2 size) {
		this->size = size;
		type = EOGL_WINDOW_RESIZE_EVENT;
	}
	CharEvent::CharEvent(unsigned int codepoint) {
		this->codepoint = codepoint;
		type = EOGL_CHAR_EVENT;
	}
	MonitorEvent::MonitorEvent(int event) {
		this->event = event;
		type = EOGL_MONITOR_EVENT;
	}
	WindowPosEvent::WindowPosEvent(glm::vec2 pos) {
		this->pos = pos;
		type = EOGL_WINDOW_POS_EVENT;
	}
}