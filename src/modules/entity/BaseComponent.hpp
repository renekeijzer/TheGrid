#pragma once
#include <exception>

struct BaseComponent
{
public:
	typedef size_t Family;
	void operator delete(void * p){ fail(); }
	void operator delete[](void * p){fail(); }

protected:
	static void fail(){
		throw std::bad_alloc();
	}
	static Family familyCounter;
};

