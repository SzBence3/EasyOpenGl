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
		virtual bool haveInput();
		virtual void pushEvent(eventType type, Event* e);
		virtual glm::vec2 getSize(glm::vec2 screenSize);
		virtual glm::vec2 getPos(glm::vec2 screenSize);
	};
}
