#pragma once
#define ANALYTICS
#ifdef ANALYTICS
#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "AnalyticsException.h"
#include <Windows.h>

class SystemManager;

class Analytics
{
public:
	static Analytics * get();
	static Analytics * get(EntityManager & man, SystemManager & sys);
	
	void log();
private:
	Analytics(EntityManager & eManager, SystemManager & sManager) : ent(eManager), sys(sManager){}
	SystemManager & sys;
	EntityManager & ent;

	static Analytics * instance;
	bool pressed = false;
};

#endif