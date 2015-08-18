#ifndef __SYSTEM__
#define __SYSTEM__

#include "BaseSystem.hpp"
#ifdef SYSTEM
class SystemManager;
template <typename Derived>
class System : public BaseSystem {
public:
	System(double interval = 0) : BaseSystem(interval){}
	virtual ~System() {}

private:
	friend class SystemManager;

	static Family family() {
		static Family family = familyCounter++;
		return family;
	}
};
#endif
#endif