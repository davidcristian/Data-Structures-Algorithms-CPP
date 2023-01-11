#include <iostream>

#include "ListIterator.h"
#include "SortedIndexedList.h"

using namespace std;

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
ListIterator::ListIterator(const SortedIndexedList& list) : list(list)
{
	this->TPosition = 0;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
void ListIterator::first()
{
	this->TPosition = 0;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
void ListIterator::next()
{
	if (this->TPosition >= list.size())
		throw std::exception();

	this->TPosition++;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
bool ListIterator::valid() const
{
	return this->TPosition < list.size();
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
TComp ListIterator::getCurrent() const
{
	if (!this->valid())
		throw std::exception();

	return list.getElement(this->TPosition);
}
