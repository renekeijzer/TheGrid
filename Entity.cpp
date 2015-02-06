#include "Entity.hpp"

const EntityId Entity::INVALID;

bool Entity::valid() const{
	return entityManager && entityManager->valid(id);
}

void Entity::invalidate() {
	id = INVALID;
	entityManager = nullptr;
}

void Entity::destroy() {
	assert(valid());
	entityManager->destroyEntity(id);
	invalidate();
}