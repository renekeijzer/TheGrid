#include "SystemManager.hpp"


void SystemManager::configure() {
	for (auto &pair : systems) {
		pair.second->configure(eventManager);
	}
	init = true;
}