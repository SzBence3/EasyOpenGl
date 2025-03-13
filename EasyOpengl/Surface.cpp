#include"Surface.h"
#include<stdexcept>

namespace eogl {

	Surface::Surface() {}
	Surface::~Surface() {}

	void Surface::Render() {
		throw std::logic_error("Not implemented");
	}
	void Surface::bindTexture(int index) {
		throw std::logic_error("Not implemented");
	}
	std::pair<glm::vec2, glm::vec2> Surface::getPosition(glm::vec2 screenSize) {
		return std::pair<glm::vec2, glm::vec2>(glm::vec2(0, 0), glm::vec2(0, 0));
	}
	bool Surface::haveInput() {
		return 0;
	}
	void Surface::pushEvent(eventType type, Event* e) {
		throw std::logic_error("Not implemented");
	}
	glm::vec2 Surface::getSize() {
		return glm::vec2(0, 0);
	}
	glm::vec2 Surface::getPos() {
		return glm::vec2(0, 0);
	}
}
