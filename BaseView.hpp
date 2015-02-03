#pragma once
#ifdef ENTITY
#ifndef BASEVIEW
#define BASEVIEW
#include "EntityManager.hpp"
#include "Entity.hpp"
#include "ViewIterator.hpp"

template <bool All>
class BaseView {
public:
	class Iterator : public ViewIterator<Iterator, All> {
	public:
		Iterator(EntityManager *emanager,
			const ComponentMask cmask,
			uint32_t index) : ViewIterator<Iterator, All>(emanager, cmask, index) {
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

	BaseView(EntityManager *emanager) : manager(emanager) { cmask.set(); }
	BaseView(EntityManager *emanager, ComponentMask cmask) :
		manager(emanager), mask(cmask) {}

	EntityManager *manager;
	ComponentMask mask;
};
#endif
#endif

#include "BaseView.hpp"