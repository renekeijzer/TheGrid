#pragma once
#include "EntityManager.hpp"
#include "Entity.hpp"
#include "EntityId.hpp"

/**
* \author: Rene Keijzer
* \version: 1.0
* \date: 22/1/2015
* \brief A componentHandle<C> is a wrapper arround an instance of a component
*		 it Provides safe acces to components. the handle wil be invalidated under the following conditions
*		 - If a component is removed from its host entity.
*		 - If its host entity is destroyed.
*/



template<typename C>
class ComponentHandle{
	typedef C ComponentType;
public:
	ComponentHandle() : manager{ nullptr }{}

	bool valid() const{
		return manager && manager->valid(id) && manager->hasComponent<ComponentType>(id);
	}
	operator bool() const{
		return valid();
	}

	ComponentType * operator->(){
		return manager->getComponentPtr<ComponentType>(id);
	}
	const ComponentType * operator->() const{
		return manager->getComponentPtr<ComponentType>(id);
	}

	ComponentType * get(){
		return manager->getComponentPtr<ComponentType>(id);
	}


	const ComponentType * get() const {
		return manager->getComponentPtr<ComponentType>(id);
	}

	void remove(){
		manager->removeComponent<ComponentType>(id);
	}

	bool operator== (const ComponentHandle<ComponentType> & other)const { return other.manager == manager && id == other.id; }
	bool operator!=(const ComponentHandle<ComponentType> & other)const { return !(*this == other); }

private:
	friend class EntityManager;

	ComponentHandle(EntityManager * oManager, EntityId oId) : manager{ oManager }, id{ oId }{}
	ComponentHandle(const EntityManager * oManager, EntityId oid) :  manager{ const_cast<EntityManager*>(oManager) }, id{ oid }{}

	EntityManager * manager;
	EntityId id;
};