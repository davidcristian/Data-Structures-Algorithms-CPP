#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	const MultiMap& col;
	int currentKey;
	Node* currentNode;

	//DO NOT CHANGE THIS PART
	MultiMapIterator(const MultiMap& c);

public:
	void first();
	void next();
	bool valid() const;
	TElem getCurrent() const;

	//moves the current element from the iterator k steps forward, or makes the iterator invalid if there are less than k elements left in the MultiMap.
	//throws an exception if the iterator is invalid or if k is 0 zero negative
	void jumpForward(int k);
};
