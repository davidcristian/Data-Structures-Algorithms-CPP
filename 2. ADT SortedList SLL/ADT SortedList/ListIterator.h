#pragma once

#include "SortedIndexedList.h"

class ListIterator
{
	//DO NOT CHANGE THIS PART
	friend class SortedIndexedList;

private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);

	int TPosition;

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
};
