#pragma once

#include "Matrix.h"

class MatrixIterator
{
private:
	//DO NOT CHANGE THIS PART
	friend class Matrix;

	MatrixIterator(const Matrix&);
	const Matrix& matrix;

	int position;

public:
	void first();
	void next();
	void previous();
	bool valid() const;
	TElem getCurrent() const;
};
