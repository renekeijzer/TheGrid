#pragma once
#include "BasePool.hpp"
template <typename T, std::size_t ChunkSize = 8192>
class Pool : public BasePool {
public:
	Pool() : BasePool(sizeof(T), ChunkSize) {}
	virtual ~Pool() {
		// Component destructors *must* be called by owner.
	}

	virtual void destroy(std::size_t n) override {
		T *ptr = static_cast<T*>(get(n));
		ptr->~T();
	}
};