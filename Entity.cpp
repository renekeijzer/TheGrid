#include "Entity.hpp"

const EntityId Entity::INVALID;

bool Entity::valid() const{
	return entityManager && entityManager->valid(id);
}