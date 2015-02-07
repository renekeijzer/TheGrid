#pragma once
#include <list>
#include <memory>

#include "BaseEvent.hpp"
class BaseReceiver {
public:
	virtual ~BaseReceiver() {
		for (auto connection : connections) {
			auto &ptr = connection.first;
			if (!ptr.expired()) {
				ptr.lock()->disconnect(connection.second);
			}
		}
	}

	// Return number of signals connected to this receiver.
	std::size_t connectedSignals() const {
		std::size_t size = 0;
		for (auto connection : connections) {
			if (!connection.first.expired()) {
				size++;
			}
		}
		return size;
	}

private:
	friend class EventManager;
	std::list<std::pair<EventSignalWeakPtr, std::size_t>> connections;
};
