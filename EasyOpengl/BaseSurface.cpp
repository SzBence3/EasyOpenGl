#include"BaseSurface.h"
#include<stdexcept>

namespace eogl {
	BaseSurface::BaseSurface(glm::vec2 pos, glm::vec2 size, bool isInput) {
		this->pos = pos;
		this->size = size;
		this->input = isInput;
		for (int i = 0; i < EOGL_EVENT_COUNT; i++) {
			callbacks[i] = nullptr;
		}
	}
	BaseSurface::BaseSurface() {
		this->pos = glm::vec2(0.0f, 0.0f);
		this->size = glm::vec2(1.0f, 1.0f);
		this->input = false;
		for (int i = 0; i < EOGL_EVENT_COUNT; i++) {
			callbacks[i] = nullptr;
		}
	}
	BaseSurface::~BaseSurface() {
		for (int i = 0; i < EOGL_EVENT_COUNT; i++) {
			if (callbacks[i] != nullptr) {
				delete callbacks[i];
			}
		}
	}
	void BaseSurface::bindTexture(int index) {
		throw std::runtime_error("Not implemented");
	}
	glm::vec2 BaseSurface::getPos(glm::vec2 screenSize) {
		return pos;
		return glm::vec2(pos.x * screenSize.x, pos.y * screenSize.y);
	}
	glm::vec2 BaseSurface::getSize(glm::vec2 screenSize) {
		return size;
		return glm::vec2(size.x * screenSize.x, size.y * screenSize.y);
	}
	bool BaseSurface::haveInput() {
		return input;
	}
	void BaseSurface::setPos(glm::vec2 pos) {
		this->pos = pos;
	}
	void BaseSurface::setSize(glm::vec2 size) {
		this->size = size;
	}
	void BaseSurface::setInput(bool input) {
		this->input = input;
	}
	void BaseSurface::pushEvent(eventType type, Event* e) {
		if (callbacks[type] != nullptr) {
			callbacks[type]->call(e);
		}
	}
}