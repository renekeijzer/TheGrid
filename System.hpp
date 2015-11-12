#pragma once
#include "BaseSystem.hpp"
#ifdef SYSTEM
class SystemManager;
template <typename Derived>
class System : public BaseSystem {
public:
	System() : BaseSystem(){}
	virtual ~System() {}

private:
	friend class SystemManager;

	static Family family() {
		static Family family = familyCounter++;
		return family;
	}
};
#endif