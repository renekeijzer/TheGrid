#pragma once
#include "EntityManager.hpp"
#include "EntityId.hpp"
#include "ComponentHandle.hpp"
#include "ViewIterator.hpp"

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
