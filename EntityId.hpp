#pragma once
#include <cstdint>

#include "EntityManager.hpp"

struct EntityId
{
	EntityId(){}
	explicit EntityId(uint64_t id) : Eid(id){}
	EntityId(uint32_t index, uint32_t version) : Eid(uint64_t(index) | uint64_t(version) << 32UL) {}

	uint64_t id() const { return Eid; }

	bool operator==(EntityId & rhs) const { return rhs.Eid == Eid; }
	bool operator!=(EntityId & rhs) const { return rhs.Eid != Eid; }

	uint32_t index() const { return Eid & 0xffffffffUL; }
	uint32_t version() const { return Eid >> 32; }
private:
	friend class EntityManager;
	uint64_t Eid;
};