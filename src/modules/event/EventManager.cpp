#include "EventManager.hpp"


EventManager::EventManager() {
}

EventManager::~EventManager() {
}

void EventManager::emit(const BaseEvent &event) {
	auto sig = signalFor(event.myFamily());
	sig->emit(&event);
}