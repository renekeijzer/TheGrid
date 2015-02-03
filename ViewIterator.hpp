#pragma once
#ifdef ENTITY
#include <iterator>

#include "EntityManager.hpp"
#include "Entity.hpp"

class Entity;
template <typename Delegate, bool All = false>
class ViewIterator : public std::iterator<std::input_iterator_tag, EntityId>{
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
	ViewIterator(){}

private:
	ComponentMask mask;
	EntityManager * manager;
	uint32_t indexPointer;
	uint32_t capacity;
	std::list<uint32_t>::iterator freeListCursor;
};
#endif