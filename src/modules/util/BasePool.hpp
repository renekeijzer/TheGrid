#pragma once
#include <vector>
#include <cassert>
class BasePool
{
public:
	explicit BasePool(std::size_t eSize, std::size_t cSize = 8192) : ElementSize(eSize), ChunckSize(cSize), Capacity(0){}
	virtual ~BasePool();

	/**
	*	Getters
	*/
	size_t getSize() const;
	size_t getChunks() const;
	size_t getCapacity() const;

	/**
	* Pool controls
	*/
	void expand(size_t n);
	void reserve(size_t n);
	void *get(size_t n);
	void *get(size_t n) const;
	virtual void destroy(size_t n) = 0;


protected:
	std::vector<char *>Blocks;
	size_t ElementSize;
	size_t ChunckSize;
	size_t Size = 0;
	size_t Capacity;

};

