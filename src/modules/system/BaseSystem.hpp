#ifndef __BASESYSTEM__
#define __BASESYSTEM__


#include "NonCopyable.hpp"
#include "EntityManager.hpp"
#include "EventManager.hpp"
class BaseSystem : public NonCopyable{
public:
	BaseSystem(double interval = 0) : Interval(interval) {}
	typedef size_t Family;

	virtual ~BaseSystem();

	virtual void configure(EventManager &events){}

	virtual void update(EntityManager &entities, EventManager &events, double dt) = 0;

	static Family familyCounter;

protected:
	double Interval = 0;
private:
	friend class SystemManager;
	double ElapsedTime = 0;
};
#define SYSTEM
#endif