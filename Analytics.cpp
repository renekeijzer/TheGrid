#include "Analytics.hpp"

#ifdef ANALYTICS
	Analytics* Analytics::instance = nullptr;

	Analytics * Analytics::get(){
		if (!instance){
			throw AnalyticsException("SystenManager and EntityManager aren't defined!");
		}
		return instance;
	}

	Analytics * Analytics::get(EntityManager & eMan, SystemManager & sMan){
		if (!instance){
			instance = new Analytics(eMan, sMan);
		}
		return instance;
	}

void Analytics::log(){
	if (GetAsyncKeyState(VK_F3) & 0x8000){
		std::cout << "pressed";
	}
	
}

#endif
