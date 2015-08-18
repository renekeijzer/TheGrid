#pragma once 
#include "BaseReceiver.hpp"

template <typename Derived>
class Receiver : public BaseReceiver {
public:
	virtual ~Receiver() {}
};