#include"Surface.h"
#include<stdexcept>

namespace eogl {

	Surface::Surface() {}
	Surface::~Surface() {}
	void Surface::bindTexture(int index) {
		throw std::logic_error("Not implemented");
	}
	std::pair<glm::vec2, glm::vec2> Surface::getPosition(glm::vec2 screenSize) {
		return std::pair<glm::vec2, glm::vec2>(glm::vec2(0, 0), glm::vec2(0, 0));
	}
	bool Surface::haveInput() {
		return 0;
	}
}
