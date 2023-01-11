#pragma once

//DO NOT INCLUDE MATRIXITERATOR

#define INITIAL_CAPACITY 16
#define CAPACITY_SCALE 2

//DO NOT CHANGE THIS PART
class MatrixIterator;
typedef int TElem;
#define NULL_TELEM 0

class Triplet
{
public:
	int row;
	int col;
	TElem val;

	Triplet() : row{ -1 }, col{ -1 }, val{ NULL_TELEM } {};
	Triplet(const int& r, const int& c, const TElem& e) : row{ r }, col{ c }, val{ e } {};
};

class Matrix
{
private:
	//DO NOT CHANGE THIS PART
	friend class MatrixIterator;

	int capacity;
	int lines;
	int columns;

	Triplet* elems;
	int* next;

	int head;
	int firstFree;

	void resize();
	int allocate();
	void release(int pos);

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);


	// returns an iterator set to the first element of the matrix or invalid if the matrix is empty
	MatrixIterator iterator();

	//creates a bi-directional iterator over all elements of the Matrix on a given line (no matter if they are NULL_TELEM or not)
	//throws exception if line is not a valid line
	MatrixIterator iterator(int line) const;

	//transforms the current matrix into its own transposed (element from position i,j, becomes element on position j,i)
	void transpose();

	//destructor
	~Matrix();
};
