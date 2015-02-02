#pragma once
#include "EntityManager.hpp"
class BaseSystem{
public:
	typedef size_t Family;

	virtual ~BaseSystem();

	virtual void configure() {}

	virtual void update(EntityManager &entities, double dt) = 0;

	static Family familyCounter;

protected:
};
