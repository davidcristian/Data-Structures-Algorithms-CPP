#include "MultiMapIterator.h"
#include "MultiMap.h"

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c)
{
	this->first();
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
TElem MultiMapIterator::getCurrent() const
{
	if (!this->valid())
		throw exception();
	
	return currentNode->tuple;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
bool MultiMapIterator::valid() const
{
	return currentNode != NULL;
}

/// <summary>
/// Complexity:
/// WC: Theta(N)
/// BC: Theta(1)
/// AC: Theta(N)
/// Total time complexity: O(N)
/// </summary>
void MultiMapIterator::next()
{
	if (!this->valid())
		throw exception();
	
	currentNode = currentNode->next;
	while (currentNode == NULL && this->currentKey + 1 < this->col.capacity)
	{
		this->currentKey++;
		currentNode = this->col.hTable[this->currentKey]->next;
	}
}

/// <summary>
/// Complexity:
/// WC: Theta(N)
/// BC: Theta(1)
/// AC: Theta(N)
/// Total time complexity: O(N)
/// </summary>
void MultiMapIterator::first()
{
	this->currentKey = 0;
	
	currentNode = this->col.hTable[this->currentKey]->next;
	while (currentNode == NULL && this->currentKey + 1 < this->col.capacity)
	{
		this->currentKey++;
		currentNode = this->col.hTable[this->currentKey]->next;
	}
}

/// <summary>
/// Complexity:
/// Theta(K)
/// </summary>
void MultiMapIterator::jumpForward(int k)
{
	if (k < 0 || !this->valid())
		throw exception();

	while (this->valid() && k-- > 0)
		this->next();
}
