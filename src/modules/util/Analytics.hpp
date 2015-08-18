#pragma once
#define ANALYTICS
#ifdef ANALYTICS
#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "EventManager.hpp"
#include "AnalyticsException.h"
#include <Windows.h>

class SystemManager;

class Analytics
{
public:
	static Analytics * get();
	static Analytics * get(EntityManager & man, SystemManager & sys, EventManager & event);
	
	void log();
private:
	Analytics(EntityManager & eManager, SystemManager & sManager, EventManager & evManager) : ent(eManager), sys(sManager), event(evManager){}
	SystemManager & sys;
	EntityManager & ent;
	EventManager & event;

	static Analytics * instance;
	bool pressed = false;
};

#endif