#pragma once

#include"Event.h"

namespace eogl{
	class EventCallback{
	public:
		virtual bool call(Event* event);
	};

	template<class T>
	class EventCallbackt : public EventCallback{
		T* func;
	public:
		EventCallbackt(T* func) {
			this->func = func;
		}
		EventCallbackt(const T& func) {
			this->func = (T*) & func;
		}	
		virtual bool call(Event* event) override{
			return func->operator()(event);
		}
	};

	template<class T>
	EventCallback* createEventCallback(const T &func) {
		return new EventCallbackt<T>(func);
	}
}