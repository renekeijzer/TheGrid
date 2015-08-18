#ifndef __COMPONENT__
#define __COMPONENT__

#include <ostream>
#include "ComponentHandle.hpp"
#include "BaseComponent.hpp"
template <typename Derived>
struct Component : public BaseComponent{
public:

	typedef ComponentHandle<Derived> Handle;
	virtual std::string toString(){ return "not implemented"; }
	static Family family();
};


template <typename C>
BaseComponent::Family Component<C>::family(){
	static Family family = familyCounter++;
	return family;
}

#endif