#pragma once
#include "Surface.h"
#include <glm/glm.hpp>
#include "EventCallback.h"

namespace eogl {
	class BaseSurface : public Surface {
	protected:
		//left down corner and right up corner
		glm::vec2 pos, size;
		EventCallback* callbacks[EOGL_EVENT_COUNT];
		bool input;
	public:
		BaseSurface(glm::vec2 pos, glm::vec2 size, bool isInput);
		BaseSurface();
		~BaseSurface();
		virtual void bindTexture(int index) override;
		//from left down corner
		virtual glm::vec2 getPos(glm::vec2 screenSize) override;
		virtual glm::vec2 getSize(glm::vec2 screenSize) override;
		virtual void setPos(glm::vec2 pos);
		virtual void setSize(glm::vec2 size);
		virtual bool haveInput() override;
		template<typename T> void setEventCallback(eventType type, T callback) {
			callbacks[type] = createEventCallback(callback);
		}
		void setPos(glm::vec2 ld, glm::vec2 ru);
		void setInput(bool input);
		void pushEvent(eventType type, Event* e) override;
	};
}