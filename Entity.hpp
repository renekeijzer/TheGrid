#pragma once
#include "EntityManager.hpp"
#include "EntityId.hpp"
#include "ComponentHandle.hpp"

#ifndef ENTITY
#define ENTITY
typedef std::bitset<64> ComponentMask;

template <typename C>
class ComponentHandle;

class Entity
{
public:
	static const EntityId INVALID;
	Entity(){}

	template<typename C, typename ... Args>
	ComponentHandle<C> addComponent(Args && ... args){ return entityManager->addComponent<C>(id, args ...); }
private:
	friend class EntityManager;
	
	Entity(EntityManager * man, EntityId Eid) : entityManager(man), id(Eid){}
	EntityId id = INVALID;
	EntityManager * entityManager;
};
#endif