#pragma once
#include "NonCopyable.hpp"
#include "EntityManager.hpp"
class BaseSystem : public NonCopyable{
public:
	typedef size_t Family;

	virtual ~BaseSystem();

	virtual void configure() {}

	virtual void update(EntityManager &entities, double dt) = 0;

	static Family familyCounter;

protected:
};
#define SYSTEM