#include "BasePool.hpp"



size_t BasePool::getSize() const { return Size; }
size_t BasePool::getChunks() const { return Blocks.size(); }
size_t BasePool::getCapacity() const { return Capacity; };


void BasePool::expand(size_t n){
	if (n >= Size){
		if (n >= Capacity)
		{
			reserve(n);
		}
		Size = n;
	}
}

void BasePool::reserve(size_t n){
	while (Capacity < n)
	{
		char *chunk = new char[ElementSize * ChunckSize];
		Blocks.push_back(chunk);
		Capacity += ChunckSize;
	}
}

void * BasePool::get(size_t n){
	assert(n < Size);
	return Blocks[n / ChunckSize] + (n % ChunckSize) * ElementSize;
}

void * BasePool::get(size_t n) const{
	assert(n < Size);
	return Blocks[n / ChunckSize] + (n % ChunckSize) * ElementSize;
}

BasePool::~BasePool() {
	for (char *ptr : Blocks) {
		delete[] ptr;
	}
}
