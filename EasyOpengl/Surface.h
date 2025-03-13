#pragma once

#include"Event.h"
#include<glm/glm.hpp>
#include<utility>

namespace eogl {
	class Surface {
	public:
		Surface();
		~Surface();
		virtual void Render();
		virtual void bindTexture(int index);
		virtual std::pair<glm::vec2, glm::vec2> getPosition(glm::vec2 screenSize);
		virtual bool haveInput();
		virtual void pushEvent(eventType type, Event* e);
		virtual glm::vec2 getSize();
		virtual glm::vec2 getPos();
	};
}
