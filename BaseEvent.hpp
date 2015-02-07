#pragma once
#include <utility>
#include <memory>
#include "SimpleSignal.hpp"
class BaseEvent
{
public:
	typedef std::size_t Family;
	
	virtual ~BaseEvent();
	
	virtual Family myFamily() const = 0;
protected:
	static Family familyCounter;
};


typedef Simple::Signal<void(const BaseEvent*)> EventSignal;
typedef std::shared_ptr<EventSignal> EventSignalPtr;
typedef std::weak_ptr<EventSignal> EventSignalWeakPtr;
