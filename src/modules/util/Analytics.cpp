#include "Analytics.hpp"

#ifdef ANALYTICS
	Analytics* Analytics::instance = nullptr;

	Analytics * Analytics::get(){
		if (!instance){
			throw AnalyticsException("SystenManager and EntityManager aren't defined!");
		}
		return instance;
	}

	Analytics * Analytics::get(EntityManager & eMan, SystemManager & sMan, EventManager & evMan){
		if (!instance){
			instance = new Analytics(eMan, sMan, evMan);
		}
		return instance;
	}

void Analytics::log(){
	if (GetAsyncKeyState(VK_F3) & 0x8000 && !pressed){
		pressed = true;


		std::cout << "=============================================" << std::endl;
		std::cout << "=               Debug information           =" << std::endl;
		std::cout << "=============================================" << std::endl;
		std::cout << std::endl;
		std::cout << "EntityManager: " << std::endl;
		std::cout << "\t Components: " << ent.ComponentPools.size() << std::endl;
		std::cout << "\t Entities managed: " << ent.EntityComponentMask.size() << std::endl;
		std::cout << "\t Free entity Slots: " << ent.FreeList.size() << std::endl;
		std::cout << std::endl;
		std::cout << "SystemManager: " << std::endl;
		std::cout << "\t Managed Systems: " << sys.systems.size() << std::endl;
		std::cout << std::endl;
		std::cout << "EventManager: " << std::endl;
		std::cout << "\t Connected Reveivers : " << event.connectedReceivers() << std::endl;
		std::cout << std::endl;
		std::cout << "=============================================" << std::endl;
	}
	else{
		pressed = false;
	}
	
}

#endif
