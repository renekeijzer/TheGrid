#ifndef __RECEIVER__
#define __RECEIVER__ 

#include "BaseReceiver.hpp"

template <typename Derived>
class Receiver : public BaseReceiver {
public:
	virtual ~Receiver() {}
};
#endif