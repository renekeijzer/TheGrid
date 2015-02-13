#pragma once
#include "NonCopyable.hpp"
#include "EntityManager.hpp"
#include "EventManager.hpp"
class BaseSystem : public NonCopyable{
public:
	typedef size_t Family;

	virtual ~BaseSystem();

	virtual void configure(EventManager &events){}

	virtual void update(EntityManager &entities, EventManager &events, double dt) = 0;

	static Family familyCounter;

protected:
};
#define SYSTEM