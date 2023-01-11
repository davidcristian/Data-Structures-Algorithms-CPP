#include <iostream>

#include "ListIterator.h"
#include "SortedIndexedList.h"

using namespace std;

/// <summary>
/// Complexity:
/// WC: Theta(log n)
/// BC: Theta(1)
/// AC: Theta(log n)
/// Total time complexity: O(log n)
/// </summary>
ListIterator::ListIterator(const SortedIndexedList& list) : list(list)
{	// Inorder search
	Node* node = list.root;
	while (node != nullptr)
	{
		stack.push(node);
		node = node->left;
	}

	if (!stack.empty())
		current = stack.top();
	else
		current = nullptr;
}

/// <summary>
/// Complexity:
/// WC: Theta(log n)
/// BC: Theta(1)
/// AC: Theta(log n)
/// Total time complexity: O(log n)
/// </summary>
void ListIterator::first()
{	// Inorder search
	stack.clear();

	Node* node = list.root;
	while (node != nullptr)
	{
		stack.push(node);
		node = node->left;
	}

	if (!stack.empty())
		current = stack.top();
	else
		current = nullptr;
}

/// <summary>
/// Complexity:
/// WC: Theta(log n)
/// BC: Theta(1)
/// AC: Theta(log n)
/// Total time complexity: O(log n)
/// </summary>
void ListIterator::next()
{
	if (!this->valid())
		throw std::exception();

	Node* node = this->stack.pop();

	if (node->right != nullptr)
	{
		node = node->right;
		while (node != nullptr)
		{
			stack.push(node);
			node = node->left;
		}
	}

	if (!stack.empty())
		current = stack.top();
	else
		current = nullptr;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
bool ListIterator::valid() const
{
	return current != nullptr;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
TComp ListIterator::getCurrent() const
{
	if (!this->valid())
		throw std::exception();

	return current->data;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
Node* ListIterator::getCurrentNode() const
{
	if (!this->valid())
		throw std::exception();

	return current;
}
