#pragma once
#include "EntityManager.hpp"

class SystemManager
{
public:
	SystemManager(EntityManager em) : entityManager(em){}
	~SystemManager();

private:
	EntityManager & entityManager;
};

