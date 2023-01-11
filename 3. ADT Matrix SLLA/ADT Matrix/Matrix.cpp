#include <exception>
#include <string>

#include "Matrix.h"
#include "MatrixIterator.h"

/// <summary>
/// Complexity:
/// Theta(INITIAL_CAPACITY)
/// </summary>
Matrix::Matrix(int nrLines, int nrCols)
{
	this->lines = nrLines;
	this->columns = nrCols;

	// Allocate the memory
	this->capacity = INITIAL_CAPACITY;

	this->elems = new Triplet[this->capacity];
	this->next = new int[this->capacity];

	for (int i = 0; i < this->capacity - 1; i++)
		this->next[i] = i + 1;

	this->next[this->capacity - 1] = -1;
	this->firstFree = 0;
	this->head = -1;
}

/// <summary>
/// Complexity:
/// Theta(CAPACITY * CAPACITY_SCALE)
/// </summary>
void Matrix::resize()
{
	int oldCapacity = this->capacity;
	this->capacity *= CAPACITY_SCALE;

	Triplet* newElems = new Triplet[this->capacity];
	int* newNext = new int[this->capacity];

	for (int i = 0; i < oldCapacity; i++)
	{
		newElems[i] = this->elems[i];
		newNext[i] = this->next[i];
	}
	for (int i = oldCapacity; i < this->capacity - 1; i++)
		newNext[i] = i + 1;

	newNext[this->capacity - 1] = -1;
	this->firstFree = oldCapacity;

	delete[] this->elems;
	delete[] this->next;

	this->elems = newElems;
	this->next = newNext;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
int Matrix::allocate() {
	if (this->firstFree == -1)
		this->resize();

	int newPos = this->firstFree;
	this->firstFree = this->next[this->firstFree];
	return newPos;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
void Matrix::release(int pos)
{
	this->next[pos] = this->firstFree;
	this->firstFree = pos;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
int Matrix::nrLines() const
{
	return this->lines;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
int Matrix::nrColumns() const
{
	return this->columns;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
bool lexicographicCompare(const TElem& e1, const TElem& e2)
{
	return std::to_string(e1).compare(std::to_string(e2)) < 0;
}

/// <summary>
/// Complexity:
/// WC: Theta(N)
/// BC: Theta(1)
/// AC: Theta(N)
/// Total time complexity: O(N)
/// </summary>
TElem Matrix::element(int i, int j) const
{
	if (i < 0 || i >= this->nrLines() || j < 0 || j >= this->nrColumns())
		throw std::exception();

	int current = this->head;
	while (current != -1)
	{
		if (this->elems[current].row == i && this->elems[current].col == j)
			return this->elems[current].val;

		current = this->next[current];
	}

	return NULL_TELEM;
}

/// <summary>
/// Complexity:
/// WC: Theta(N)
/// BC: Theta(1)
/// AC: Theta(N)
/// Total time complexity: O(N)
/// </summary>
TElem Matrix::modify(int i, int j, TElem e)
{
	if (i < 0 || i >= this->nrLines() || j < 0 || j >= this->nrColumns())
		throw std::exception();
	
	// Check if the row and column exist in the matrix
	int previous = -1;
	int current = this->head;
	while (current != -1)
	{
		// Found the position
		if (this->elems[current].row == i && this->elems[current].col == j)
		{
			// We want to add a NULL_TELEM
			// so delete the position
			if (e == NULL_TELEM)
			{
				TElem oldValue = this->elems[current].val;
				
				// Set pointers correctly
				if (current == this->head)
					this->head = this->next[this->head];
				else
					this->next[previous] = this->next[current];

				// Mark position as free
				this->release(current);
				return oldValue;

			}
			else
			{	// We want to add a non-null element
				TElem oldValue = this->elems[current].val;
				this->elems[current].val = e;

				// If this is not the first node
				// move it to the lexicographic position
				if (current != this->head)
				{
					// save current position
					int newPos = current;

					// set pointer from previous to next
					this->next[previous] = this->next[current];

					// find correct lexicographic position
					previous = -1;
					current = this->head;
					while (current != -1 && lexicographicCompare(this->elems[current].val, e))
					{
						previous = current;
						current = this->next[current];
					}

					// the elem needs to be added in the first position
					if (current == this->head)
					{
						if (this->head != -1)
							this->next[newPos] = this->head;

						this->head = newPos;
					}
					else
					{	// insert between previous and current
						this->next[newPos] = current;
						this->next[previous] = newPos;
					}
				}

				return oldValue;
			}
		}

		previous = current;
		current = this->next[current];
	}

	// The row and column do not exist and we want to add
	// a NULL_TELEM don't do anything in this case
	if (e == NULL_TELEM)
		return NULL_TELEM;

	// Find the position where the lexicographic check fails
	previous = -1;
	current = this->head;
	while (current != -1 && lexicographicCompare(this->elems[current].val, e))
	{
		previous = current;
		current = this->next[current];
	}

	// allocate new elem
	int newPos = this->allocate();

	// create the elem
	this->elems[newPos] = Triplet{ i, j, e };
	this->next[newPos] = -1;

	// the elem needs to be added in the first position
	if (current == this->head)
	{
		if (this->head != -1)
			this->next[newPos] = this->head;

		this->head = newPos;
	}
	else
	{	// insert between previous and current
		this->next[newPos] = current;
		this->next[previous] = newPos;
	}

	return NULL_TELEM;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
MatrixIterator Matrix::iterator()
{
	return MatrixIterator(*this);
}

/// <summary>
/// Complexity:
/// WC: Theta(N)
/// BC: Theta(1)
/// AC: Theta(N)
/// Total time complexity: O(N)
/// </summary>
MatrixIterator Matrix::iterator(int line) const
{
	if (line < 0 || line >= this->nrLines())
		throw std::exception();

	Matrix* m = new Matrix(1, this->nrColumns());

	int current = this->head;
	while (current != -1)
	{
		if (this->elems[current].row == line)
			m->modify(0, this->elems[current].col, this->elems[current].val);
	
		current = this->next[current];
	}

	return MatrixIterator(*m);
}

/// <summary>
/// Complexity:
/// WC: Theta(N)
/// BC: Theta(1)
/// AC: Theta(N)
/// Total time complexity: O(N)
/// </summary>
void Matrix::transpose()
{
	int current = this->head;
	while (current != -1)
	{
		int tmp = this->elems[current].row;
		this->elems[current].row = this->elems[current].col;
		this->elems[current].col = tmp;

		current = this->next[current];
	}
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
Matrix::~Matrix()
{
	delete[] this->elems;
	delete[] this->next;
}
