#pragma once
#include "ComponentHandle.hpp"
#include "BaseComponent.hpp"
template <typename Derived>
struct Component : public BaseComponent{
public:

	typedef ComponentHandle<Derived> Handle;
	static Family family();
};


template <typename C>
BaseComponent::Family Component<C>::family(){
	static Family family = familyCounter++;
	return family;
}