#pragma once
#include <iterator>

#include "EntityManager.hpp"
#include "Entity.hpp"

template < typename Delgate, bool debug = false>
class ViewIterator : public std::iterator<std::input_iterator_tag, EntityId>{



private:
	EntityManager * manager;
	uint32_t indexPointer;
};