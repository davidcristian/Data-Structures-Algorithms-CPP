#include <iostream>
#include <exception>
#include "MultiMap.h"
#include "MultiMapIterator.h"

using namespace std;

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
int MultiMap::hash(TKey k) const
{
	// negative number, make it positive
	while (k < 0)
		k += this->capacity;

	// return hashed key
	return abs(k) % this->capacity;
}

/// <summary>
/// Complexity:
/// Theta(INITIAL_CAPACITY)
/// </summary>
MultiMap::MultiMap()
{
	// allocate the memory
	this->capacity = INITIAL_CAPACITY;
	this->hTable = new Node * [this->capacity];

	// init keys
	for (int i = 0; i < this->capacity; ++i)
		this->hTable[i] = new Node{};

	this->nrPairs = 0;
}

/// <summary>
/// Complexity:
/// Theta(CAPACITY * CAPACITY_SCALE)
/// </summary>
void MultiMap::resize()
{
	int oldCapacity = this->capacity;
	this->capacity *= CAPACITY_SCALE;

	Node** newTable;
	newTable = new Node * [this->capacity];

	for (int i = 0; i < this->capacity; ++i)
		newTable[i] = new Node{};

	for (int i = 0; i < oldCapacity; ++i)
	{
		Node* current = this->hTable[i];
		while (current->next != NULL)
		{
			current = current->next;

			Node* newNode = new Node{ current->tuple.key, current->tuple.val, nullptr };
			int k = hash(newNode->tuple.key);

			Node* head = newTable[k];
			while (head->next != NULL)
				head = head->next;

			head->next = newNode;
		}
	}

	for (int i = 0; i < oldCapacity; ++i)
		release(this->hTable[i]);

	delete[] this->hTable;
	this->hTable = newTable;
}

/// <summary>
/// Complexity:
/// WC: Theta(N)
/// BC: Theta(1)
/// AC: Theta(N)
/// Total time complexity: O(N)
/// </summary>
void MultiMap::add(TKey c, TValue v)
{
	// create new node
	Node* newNode = new Node{ c, v, nullptr };

	// if the load is nearing max, resize
	if (double(this->nrPairs) / this->capacity > MAX_LOAD)
		this->resize();
	
	// get the hashed key
	int k = hash(c);

	// get the chain head
	Node* current = this->hTable[k];
	
	// find tail of chain
	while (current->next != NULL)
		current = current->next;
	current->next = newNode;

	this->nrPairs++;
}

/// <summary>
/// Complexity:
/// WC: Theta(N)
/// BC: Theta(1)
/// AC: Theta(N)
/// Total time complexity: O(N)
/// </summary>
bool MultiMap::remove(TKey c, TValue v)
{
	// get the hashed key
	int k = hash(c);

	Node* nextNode = nullptr;
	// get the chain head
	Node* current = this->hTable[k];

	// loop through the chain, next is the first elem
	while (current->next != NULL)
	{
		nextNode = current->next;
		// if the value is found, set the pointers accordingly and release the Node
		if (nextNode->tuple.val == v)
		{
			current->next = nextNode->next;
			this->nrPairs--;

			delete nextNode;
			return true;
		}

		current = nextNode;
	}

	// no key exists
	return false;
}

/// <summary>
/// Complexity:
/// WC: Theta(N)
/// BC: Theta(1)
/// AC: Theta(N)
/// Total time complexity: O(N)
/// </summary>
vector<TValue> MultiMap::search(TKey c) const
{
	vector<TValue> ret;
	// get the hashed key
	int k = this->hash(c);

	// get the chain head
	Node* current = this->hTable[k];
	
	// loop through the chain, next is the first elem
	while (current->next != NULL)
	{
		current = current->next;

		// store the value
		ret.push_back(current->tuple.val);
	}

	return ret;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
int MultiMap::size() const
{
	return this->nrPairs;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
bool MultiMap::isEmpty() const
{
	return this->nrPairs == 0;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
MultiMapIterator MultiMap::iterator() const
{
	return MultiMapIterator(*this);
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
void MultiMap::release(Node* n)
{
	// release every Node recursively
	if (n->next != NULL)
		release(n->next);

	delete n;
}

/// <summary>
/// Complexity:
/// WC: Theta(N)
/// BC: Theta(1)
/// AC: Theta(N)
/// Total time complexity: O(N)
/// </summary>
MultiMap::~MultiMap()
{
	// loop through every key, for every key release the chain
	for (int i = 0; i < this->capacity; ++i)
		release(this->hTable[i]);
	
	delete this->hTable;
}
