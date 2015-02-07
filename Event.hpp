#pragma once
#include "BaseEvent.hpp"
template <typename Derived>
class Event : public BaseEvent{
public:
	Static Family family(){
		static Family family = familyCounter++;
		return family;
	}

	virtual Family myFamily() const override { return Derived::family(); }


};