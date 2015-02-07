#pragma once
#include <bitset>
#include <vector>
#include <list>
#include <new>
#include <iostream>
#include <iterator>

#include "BaseComponent.hpp"
#include "Component.hpp"
#include "Entity.hpp"
#include "ComponentHandle.hpp"
#include "BasePool.hpp"
#include "Pool.hpp"
#include "EntityId.hpp"
#include "Analytics.hpp"
#include "NonCopyAble.h"


typedef std::bitset<64> ComponentMask;
class Entity;

template<bool All = false>
class BaseView;

class EntityManager : public NonCopyable
{
public:
	EntityManager();
	~EntityManager();


#ifdef ENTITY
	template <typename Delegate, bool All = false>
	class ViewIterator : public std::iterator<std::input_iterator_tag, EntityId>{
	public: 
		Delegate &operator++(){
			indexPointer++;
			next();
			return *static_cast<Delegate *>(this);
		}

		bool operator==(const Delegate & rhs) const { return rhs.indexPointer == indexPointer; }
		bool operator!=(const Delegate & rhs) const { return rhs.indexPointer != indexPointer; }


		Entity operator*(){
			return Entity(manager, manager->createId(indexPointer));
		}


		const Entity operator*() const {
			return Entity(manager, manager->createId(indexPointer));
		}

	protected:
		ViewIterator(EntityManager * emanager, uint32_t index) : manager(emanager), indexPointer(index), capacity(manager->capacity()){
			if (All){
				manager->FreeList.sort();
				freeListCursor = manager->FreeList.begin();
			}
		}
		ViewIterator(EntityManager * emanager, const ComponentMask cMask, uint32_t index) : manager(emanager), mask(cMask), indexPointer(index), capacity(manager->capacity()){
			if (All){
				manager->FreeList.sort();
				freeListCursor = manager->FreeList.begin();
			}
		}


		void next() {
			while (indexPointer < capacity && !predicate()) {
				++indexPointer;
			}

			if (indexPointer < capacity) {
#ifdef VIEWDEBUG
				std::cout << "EntityId = \t" << indexPointer << "\r\n";
				std::cout << "mask = \t\t" << mask << "\r\n";
				std::cout << "cmask = \t" << manager->EntityComponentMask[indexPointer] << "\r\n";
#endif	
				Entity entity = manager->get(manager->createId(indexPointer));
			
					static_cast<Delegate*>(this)->next_entity(entity);
				
			}
		}

		inline bool predicate() {
			return (All && valid_entity()) || (manager->EntityComponentMask[indexPointer] & mask) == mask;
		}

		inline bool valid_entity() {
			if (freeListCursor != manager->FreeList.end() && *freeListCursor == indexPointer) {
				++freeListCursor;
				return false;
			}
			return true;
		}

	private:
		ComponentMask mask;
		EntityManager * manager;
		uint32_t indexPointer;
		uint32_t capacity;
		std::list<uint32_t>::iterator freeListCursor;
	};



	template <bool All>
	class BaseView {
	public:
		class Iterator : public ViewIterator<Iterator, All> {
		public:
			Iterator(EntityManager *emanager, const ComponentMask cmask, uint32_t index) : ViewIterator<Iterator, All>(emanager, cmask, index) {
					ViewIterator<Iterator, All>::next();
				}

			void next_entity(Entity &entity) {}
		};


		Iterator begin() { return Iterator(manager, mask, 0); }
		Iterator end() { return Iterator(manager, mask, uint32_t(manager->capacity())); }
		const Iterator begin() const { return Iterator(manager, mask, 0); }
		const Iterator end() const { return Iterator(manager, mask, manager->capacity()); }

	private:
		friend class EntityManager;

		BaseView(EntityManager *emanager) : manager(emanager) { mask.set(); }
		BaseView(EntityManager *emanager, ComponentMask cmask) : manager(emanager), mask(cmask) {}

		EntityManager *manager;
		ComponentMask mask;
	};

	
#endif
	typedef BaseView<false> View;
	typedef BaseView<true> DebugView;



	Entity createEntity();
	void destroyEntity(EntityId id);


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
	
	/**
	*	method creating mask accordingly by components
	*	method to get components
	*	method to get Component of entity
	*
	*
	*/

	template <typename ... Components>
	View withComponents() {
		auto mask = componentMask<Components ...>();
		return View(this, mask);
	}


	template<typename C>
	ComponentHandle<C> getComponent(EntityId id){
		if (!hasComponent<C>(id)){
			return ComponentHandle<C>();
		}
		return ComponentHandle<C>(this, id);
	}

	template<typename C>
	bool hasComponent(EntityId id){
		size_t family = C::family();
		if (family >= ComponentPools.size())
		{
			return false;
		}
		BasePool * pool = ComponentPools[family];
		if (!pool || !EntityComponentMask[id.index()][family]){
			return false;
		}
		return true;

	}

	template <typename C>
	void removeComponent(EntityId id){
		const BaseComponent::Family fam = C::family();
		const uint32_t index = id.index();
		BasePool* pool = ComponentPools[fam];
		EntityComponentMask[index].reset(fam);
		pool->destroy(index);
	}


	EntityId createId(uint32_t id){
		return EntityId(id, EntityVersion[id]);
	}

	bool valid(EntityId id);


	size_t capacity();
	size_t size();
	Entity get(EntityId id);


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

	ComponentMask componentMask(EntityId id) {
		return EntityComponentMask.at(id.index());
	}

	template <typename C>
	ComponentMask componentMask() {
		ComponentMask mask;
		mask.set(C::family());
		return mask;
	}

	template <typename C1, typename C2, typename ... Components>
	ComponentMask componentMask() {
		return componentMask<C1>() | componentMask<C2, Components ...>();
	}

	template <typename C>
	ComponentMask componentMask(const ComponentHandle<C> &c) {
		return componentMask<C>();
	}

	template <typename C1, typename ... Components>
	ComponentMask componentMask(const ComponentHandle<C1> &c1, const ComponentHandle<Components> &... args) {
		return componentMask<C1, Components ...>();
	}

#ifdef ANALYTICS
	friend class Analytics;
#endif	
	friend class Entity;
	uint32_t indexPointer = 0;
	std::vector<ComponentMask> EntityComponentMask;
	std::vector<BasePool*> ComponentPools;
	std::vector<uint32_t>EntityVersion;
	std::list<uint32_t> FreeList;
};