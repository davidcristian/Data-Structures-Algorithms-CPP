#include <exception>

#include "MatrixIterator.h"
#include "Matrix.h"

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
MatrixIterator::MatrixIterator(const Matrix& matrix) : matrix(matrix)
{
	this->position = this->matrix.head;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
void MatrixIterator::first()
{
	this->position = this->matrix.head;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
void MatrixIterator::next()
{
	if (this->position == -1)
		throw std::exception();

	this->position = this->matrix.next[position];
}

/// <summary>
/// Complexity:
/// Theta(POSITION)
/// </summary>
void MatrixIterator::previous()
{
	if (this->position == this->matrix.head)
		throw std::exception();

	for (int current = this->matrix.head; current != this->position; current = this->matrix.next[current])
	{
		if (this->matrix.next[current] == this->position)
		{
			this->position = current;
			return;
		}
	}

	throw std::exception();
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
bool MatrixIterator::valid() const
{
	return this->position != -1;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
TElem MatrixIterator::getCurrent() const
{
	if (this->position == -1)
		throw std::exception();

	return this->matrix.elems[position].val;
}
