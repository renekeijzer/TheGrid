#ifndef __ENTITY__
#define __ENTITY__

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
	EntityId getId(){ return id; }
	const EntityId getId() const { return id; }
	bool valid() const;

	template<typename C, typename ... Args>
	ComponentHandle<C> addComponent(Args && ... args){ return entityManager->addComponent<C>(id, args ...); }
	template <typename C>
	ComponentHandle<C> getComponent(){ return entityManager->getComponent<C>(id); }
	template<typename C>
	const ComponentHandle<C> getComponent() const { return entityManager->getComponent<C>(id); }

	template <typename C>
	void removeComponent(){ entityManager->removeComponent<C>(id); }
	template <typename C>
	bool hasComponent(){ return entityManager->hasComponent<C>(id); }

	template <typename C>
	const bool hasComponent() const { return entityManager->hasComponent<C>(id); }

	void invalidate();
	void destroy();
	bool operator !=(Entity & rhs){
		return id != rhs.id;
	}

	bool operator ==(Entity & rhs)
	{
		return id == rhs.id;
	}
private:
	friend class EntityManager;
	
	Entity(EntityManager * man, EntityId Eid) : entityManager(man), id(Eid){}
	EntityId id = INVALID;
	EntityManager * entityManager;
};
#endif
#endif