#pragma once
#include <bitset>
#include <vector>
#include <list>
#include <new>
#include <iostream>

#include "BaseComponent.hpp"
#include "Component.hpp"
#include "Entity.hpp"
#include "ComponentHandle.hpp"
#include "BasePool.hpp"
#include "Pool.hpp"

typedef std::bitset<64> ComponentMask;
class Entity;



class EntityManager
{
public:
	EntityManager();
	~EntityManager();


	Entity createEntity();



	template <typename C, typename ... Args>
	ComponentHandle<C> addComponent(EntityId id, Args && ... args){
		const BaseComponent::Family family = C::family();
		Pool<C> *pool = AccomodateComponent<C>();
		new(pool->get(id.index())) C(std::forward<Args>(args) ...);
		EntityComponentMask[id.index()].set(family);
		ComponentHandle<C> component(this, id);
		return component;
	}
	

	template <typename C>
	C * getComponentPtr(EntityId id)
	{
		BasePool * pool = ComponentPools[C::family()];
		return static_cast<C*>(pool->get(id.index()));
	}

	template <typename C>
	C * getComponentPtr(EntityId id) const{

		BasePool * pool = ComponentPools[C::family()];
		return static_cast<const C*>(pool->get(id.index()));
	}

private:
	template <typename C>
	Pool<C>* AccomodateComponent(){
		BaseComponent::Family family = C::family();
		if (ComponentPools.size() <= family) {
			ComponentPools.resize(family + 1, nullptr);
		}
		if (!ComponentPools[family]) {
			Pool<C> *pool = new Pool<C>();
			pool->expand(indexPointer);
			ComponentPools[family] = pool;
		}
		return static_cast<Pool<C>*>(ComponentPools[family]);
	}

	void AccomodateEntity(uint32_t id){
		if (EntityComponentMask.size() <= id){
			EntityComponentMask.resize(id + 1);
			EntityVersion.resize(id + 1);
		
			for (BasePool * pool : ComponentPools){
				if (pool){
					pool->expand(id + 1);
				}
			}
		}
	}



	friend class Entity;
	uint32_t indexPointer = 0;
	std::vector<ComponentMask> EntityComponentMask;
	std::vector<BasePool*> ComponentPools;
	std::vector<uint32_t>EntityVersion;
	std::list<uint32_t> FreeList;
};
