#include <exception>

#include "SortedSetIterator.h"

using namespace std;

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	index = 0;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
void SortedSetIterator::first()
{
	index = 0;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
void SortedSetIterator::next()
{
	if (index >= multime.length)
		throw std::exception();

	index++;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
TElem SortedSetIterator::getCurrent()
{
	if (index >= multime.length)
		throw std::exception();

	return multime.data[index];
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>	
bool SortedSetIterator::valid() const
{
	return index < multime.length;
}
