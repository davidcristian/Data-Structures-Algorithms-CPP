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
	this->root = nullptr;
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
/// WC: Theta(log n)
/// BC: Theta(1)
/// AC: Theta(log n)
/// Total time complexity: O(log n)
/// </summary>
TComp SortedIndexedList::getElement(int pos) const
{
	if (this->size() == 0 || pos < 0 || pos >= this->size())
		throw std::exception();

	int index = 0;

	stack<Node*> stack;
	Node* current = this->root;

	// loop through all nodes
	while (current != nullptr || stack.empty() == false)
	{
		// create leftmost subtree of nodes
		while (current != nullptr)
		{
			stack.push(current);
			current = current->left;
		}

		// current is null, we have reached the leftmost node
		current = stack.pop();

		// check if position was found
		if (index == pos)
			return current->data;

		// start checking nodes on the right subtree
		current = current->right;

		index++;
	}

	return NULL_TCOMP;
}

/// <summary>
/// Complexity:
/// WC: Theta(log n)
/// BC: Theta(1)
/// AC: Theta(log n)
/// Total time complexity: O(log n)
/// </summary>
TComp SortedIndexedList::remove(int pos)
{
	if (this->size() == 0 || pos < 0 || pos >= this->size())
		throw std::exception();

	TComp e = this->getElement(pos);

	Node* current = root;
	Node* prev = nullptr;

	// check if the elem is in the BST
	// prev = parent of elem
	while (current != nullptr && current->data != e)
	{
		prev = current;
	
		// relation passes, check left
		if (relation(e, current->data))
		{
			current = current->left;
		}
		else // relation fails, check right
		{
			current = current->right;
			
			if (current != nullptr)
				current->numToleft--;
		}
	}

	// elem not in BST
	if (current == nullptr)
		return NULL_TCOMP;

	// check if the node of the elem has 0 or 1 children
	if (current->left == nullptr || current->right == nullptr)
	{
		// newCurrent = the node that takes the place of the deleted node
		Node* newCurrent;

		// set newCurrent to the correct child
		if (current->left == nullptr)
			newCurrent = current->right;
		else
			newCurrent = current->left;

		// we want to delete the root
		// so update it to point to the correct branch
		if (prev == nullptr)
		{
			this->root = newCurrent;
			this->length--;
			return e;
		}

		// update the pointers of the parent
		if (current == prev->left)
			prev->left = newCurrent;
		else
			prev->right = newCurrent;

		// free deleted node
		delete current;
		this->length--;
		return e;
	}
	else // node of the elem has 2 children
	{
		Node* temp = current->right;
		Node* sucessor = nullptr;

		// find the successor node (next one based on relation)
		while (temp->left != nullptr)
		{
			sucessor = temp;
			temp = temp->left;
		}

		// update the pointers
		if (sucessor != nullptr)
			sucessor->left = temp->right;
		else
			current->right = temp->right;

		current->data = temp->data;

		// free deleted node
		delete temp;
		this->length--;
		return e;
	}

	return NULL_TCOMP;
}

/// <summary>
/// Complexity:
/// WC: Theta(log n)
/// BC: Theta(1)
/// AC: Theta(log n)
/// Total time complexity: O(log n)
/// </summary>
int SortedIndexedList::search(TComp e) const
{
	int index = 0;

	// loop through all nodes
	Node* current = this->root;
	while (current != nullptr)
	{
		// keep looping subtrees until elem is found
		if (e == current->data)
			return index; // elem found, return index

		if (relation(e, current->data))
			current = current->left; // relation passes, check left
		else
			current = current->right; // relation fails, check right

		index++;
	}

	// elem not found
	return -1;
}

/// <summary>
/// Complexity:
/// WC: Theta(log n)
/// BC: Theta(1)
/// AC: Theta(log n)
/// Total time complexity: O(log n)
/// </summary>
void SortedIndexedList::add(TComp e)
{
	Node* newNode = new Node(e, nullptr, nullptr, 0);

	Node* current = this->root;
	Node* prev = nullptr;

	// find parent
	while (current != nullptr)
	{
		prev = current; // save current Node as parent

		if (relation(e, current->data))
		{	// relation passes, check left
			current = current->left;
		}
		else
		{	// relation fails, check right
			current = current->right;
			newNode->numToleft++;
		}
	}

	// no parent, newNode is the new root
	if (prev == nullptr)
	{
		prev = newNode;
		root = prev;
	}
	else if (relation(e, prev->data))
		prev->left = newNode; // relation passes, newNode goes to the left of parent
	else
		prev->right = newNode; // relation fails, newNode goes to the right of parent

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
/// Theta(1)
/// </summary>
void SortedIndexedList::destroyTree(Node* node)
{
	if (node == nullptr) return;

	// recursively destroy all nodes of BST
	destroyTree(node->left);
	destroyTree(node->right);

	delete node;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
SortedIndexedList::~SortedIndexedList()
{
	this->destroyTree(this->root);
}

/// <summary>
/// Complexity:
/// WC: Theta(N * log n)
/// BC: Theta(1)
/// AC: Theta(N * log n)
/// Total time complexity: O(N * log n)
/// </summary>
void SortedIndexedList::removeBetween(int start, int end)
{
	if (this->isEmpty() || start < 0 || start >= this->size()
	 || start > end || end < 0 || end >= this->size())
		throw std::exception();

	int num = end - start + 1;

	while (num-- > 0)
		this->remove(start);
}
