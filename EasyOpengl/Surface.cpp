#include"Surface.h"
#include<stdexcept>

namespace eogl {

	Surface::Surface() {}
	Surface::~Surface() {}

	void Surface::Render() {}
	void Surface::bindTexture(int index) {
		throw std::logic_error("Not implemented");
	}
	bool Surface::haveInput() {
		return 0;
	}
	void Surface::pushEvent(eventType type, Event* e) {
		throw std::logic_error("Not implemented");
	}
	glm::vec2 Surface::getSize(glm::vec2 screensize) {
		return glm::vec2(0, 0);
	}
	glm::vec2 Surface::getPos(glm::vec2 screensize) {
		return glm::vec2(0, 0);
	}
}
