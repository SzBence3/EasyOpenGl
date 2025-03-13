#pragma once
#include "Surface.h"
#include <glm/glm.hpp>
#include "EventCallback.h"

namespace eogl {
	class BaseSurface : public Surface {
	protected:
		//left down corner and right up corner
		glm::vec2 ld, ru;
		EventCallback* callbacks[EOGL_EVENT_COUNT];
		bool input;
	public:
		BaseSurface(glm::vec2 ld, glm::vec2 rd, bool isInput);
		BaseSurface();
		~BaseSurface();
		virtual void bindTexture(int index) override;
		virtual std::pair<glm::vec2, glm::vec2> getPosition(glm::vec2 screenSize) override;
		virtual bool haveInput() override;
		template<typename T> void setEventCallback(eventType type, T callback) {
			callbacks[type] = createEventCallback(callback);
		}
		void setPos(glm::vec2 ld, glm::vec2 ru);
		void setInput(bool input);
		void pushEvent(eventType type, Event* e) override;
	};
}