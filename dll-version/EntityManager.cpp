#include "EntityManager.hpp"


EntityManager::EntityManager()
{
	EntityComponentMask.clear();
	
}


EntityManager::~EntityManager()
{
}

bool EntityManager::valid(EntityId id){
		return id.index() < EntityVersion.size() && EntityVersion[id.index()] == id.version();
}


Entity EntityManager::get(EntityId id){
	return Entity(this, id);
}

Entity EntityManager::createEntity(){
	uint32_t index, version;
	if (FreeList.empty()){
		index = indexPointer++;
		AccomodateEntity(index);
		version = EntityVersion[index] = 1;
	}
	else
	{
		index = FreeList.front();
		FreeList.pop_front();
		version = EntityVersion[index];
	}
	Entity entity(this, EntityId(index, version));
	return entity;
}

/**
*	@return current capacity of the entityManager
*/
size_t EntityManager::capacity(){
	return EntityComponentMask.size();
}
/**
*	@return number of managed Entities
*/
size_t EntityManager::size(){
	return EntityComponentMask.size() - FreeList.size();
}


void EntityManager::destroyEntity(EntityId id){
	uint32_t index = id.index();
	auto mask = EntityComponentMask[index];

	for (size_t i = 0; i < ComponentPools.size(); i++){
		BasePool * pool = ComponentPools[i];
		if (pool && mask.test(i)){
			pool->destroy(index);
		}
	}

	EntityComponentMask[index].reset();
	EntityVersion[index]++;
	FreeList.push_back(index);

}