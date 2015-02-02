#pragma once
#include <cstdint>

#include "EntityManager.hpp"

struct EntityId
{
	EntityId(){}
	explicit EntityId(uint64_t id) : Eid(id){}
	EntityId(uint32_t id, uint32_t version) : Eid(uint64_t(version) | uint64_t(id) << 32){}

	uint64_t id() const { return Eid; }

	bool operator==(EntityId & rhs) const { return rhs.Eid == Eid; }
	bool operator!=(EntityId & rhs) const { return rhs.Eid != Eid; }

	uint32_t index(){ return Eid >> 32; }
	uint32_t version(){ return Eid & 0xffffffff; }
private:
	friend class EntityManager;
	uint64_t Eid;
};