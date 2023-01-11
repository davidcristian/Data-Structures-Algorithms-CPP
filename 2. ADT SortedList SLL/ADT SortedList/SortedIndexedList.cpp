#include <iostream>
#include <exception>

#include "ListIterator.h"
#include "SortedIndexedList.h"

using namespace std;

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
SortedIndexedList::SortedIndexedList(Relation r)
{
	this->relation = r;
	this->head = nullptr;
	this->length = 0;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
int SortedIndexedList::size() const
{
	return this->length;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
bool SortedIndexedList::isEmpty() const
{
	return this->length == 0;
}

/// <summary>
/// Complexity:
/// WC: Theta(n)
/// BC: Theta(1)
/// AC: Theta(n)
/// Total time complexity: O(n)
/// </summary>
TComp SortedIndexedList::getElement(int i) const
{
	if (this->size() == 0 || i < 0 || i >= this->size())
		throw std::exception();

	int position = 0;
	for (Node* current = this->head; current != nullptr; current = current->next)
	{ // loop through all nodes
		if (position++ == i) // if the position is found, return the elem
			return current->data;
	}
}

/// <summary>
/// Complexity:
/// WC: Theta(n)
/// BC: Theta(1)
/// AC: Theta(n)
/// Total time complexity: O(n)
/// </summary>
TComp SortedIndexedList::remove(int i)
{
	if (this->size() == 0 || i < 0 || i >= this->size())
		throw std::exception();

	TComp ret = NULL_TCOMP;
	Node* current = this->head;
	if (i == 0)
	{ // remove the head
		ret = current->data; // store the ret value
		this->head = current->next; // set the head to the next node

		delete current; // delete the node
	}
	else
	{ // remove elem not at index 0
		for (int j = 0; j < i - 1; j++)
			current = current->next; // get elem before the one we need to remove

		Node* temp = current->next->next; // store the node after the deleted elem

		ret = current->next->data; // store the ret value
		delete current->next; // delete the elem at the index

		current->next = temp; // set the next node for current to the one found after the deleted elem
	}

	this->length--;
	return ret;
}

/// <summary>
/// Complexity:
/// WC: Theta(n)
/// BC: Theta(1)
/// AC: Theta(n)
/// Total time complexity: O(n)
/// </summary>
int SortedIndexedList::search(TComp e) const
{
	int position = 0;
	for (Node* current = this->head; current != nullptr; current = current->next)
	{ // loop through all nodes
		if (current->data == e)
			return position; // if the elem is found, return the pos

		position++;
	}

	return -1; // elem not found
}

/// <summary>
/// Complexity:
/// WC: Theta(n)
/// BC: Theta(1)
/// AC: Theta(n)
/// Total time complexity: O(n)
/// </summary>
void SortedIndexedList::add(TComp e)
{
	Node* newNode = new Node(e, nullptr);

	Node* temp = this->head;
	if (temp == nullptr || !relation(temp->data, newNode->data))
	{ // if the head is null or the new elem needs to be first
		newNode->next = temp;
		this->head = newNode;
	}
	else
	{
		while (temp->next != nullptr && relation(temp->next->data, newNode->data))
			temp = temp->next; // find the elem where the relation fails

		newNode->next = temp->next; // insert the new node to the correct place
		temp->next = newNode; // before temp->next(=relation fail)
	}

	this->length++;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
ListIterator SortedIndexedList::iterator()
{
	return ListIterator(*this);
}

/// <summary>
/// Complexity:
/// Theta(n)
/// </summary>
int SortedIndexedList::lastIndexOf(TComp e) const
{
	int position = -1;
	Node* current = this->head;

	for (int i = 0; i < this->size(); i++)
	{
		if (current->data == e)
			position = i;

		current = current->next;
	}

	return position;
};

/// <summary>
/// Complexity:
/// Theta(n)
/// </summary>
SortedIndexedList::~SortedIndexedList()
{
	while (this->head != nullptr)
	{ // keep deleting and setting the head to the next node until it is null
		Node* temp = this->head;
		this->head = this->head->next;

		delete temp;
	}
}
