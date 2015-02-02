#include "EntityManager.hpp"


EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
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