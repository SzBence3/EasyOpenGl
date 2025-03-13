#pragma once

#include<glm/glm.hpp>
#include<utility>

namespace eogl {
	class Surface {
	public:
		Surface();
		~Surface();
		virtual void bindTexture(int index);
		virtual std::pair<glm::vec2, glm::vec2> getPosition(glm::vec2 screenSize);
		virtual bool haveInput();

	};
}
