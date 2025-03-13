#include"BaseSurface.h"
#include<stdexcept>

namespace eogl {
	BaseSurface::BaseSurface(glm::vec2 ld, glm::vec2 rd, bool isInput) {
		this->ld = ld;
		this->ru = rd;
		this->input = isInput;
		for (int i = 0; i < EOGL_EVENT_COUNT; i++) {
			callbacks[i] = nullptr;
		}
	}
	BaseSurface::BaseSurface() {
		this->ld = glm::vec2(0.0f, 0.0f);
		this->ru = glm::vec2(1.0f, 1.0f);
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
	std::pair<glm::vec2, glm::vec2> BaseSurface::getPosition(glm::vec2 screenSize) {
		return std::make_pair(ld, ru);
	}
	bool BaseSurface::haveInput() {
		return input;
	}
	void BaseSurface::setPos(glm::vec2 ld, glm::vec2 ru) {
		this->ld = ld;
		this->ru = ru;
	}
	void BaseSurface::setInput(bool input) {
		this->input = input;
	}
	void BaseSurface::callEvent(eventType type, Event* e) {
		if (callbacks[type] != nullptr) {
			callbacks[type]->call(e);
		}
	}
}