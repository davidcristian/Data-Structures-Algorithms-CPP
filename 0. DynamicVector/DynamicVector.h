#pragma once

template <class TElem>
class DynamicVector
{
private:
	TElem* data;
	int capacity;
	
	int length;

	/// <summary>
	/// Resizes the data if the capacity is full
	/// </summary>
	void resize()
	{
		this->capacity *= 2;
		TElem* newElems = new TElem[this->capacity];
		for (int i = 0; i < this->length; ++i)
			newElems[i] = this->data[i];

		delete[] this->data;
		this->data = newElems;
	};

public:
	/// <summary>
	/// Constructs the DynamicVector
	/// </summary>
	/// <param name="capacity">the initial capacity of the vector</param>
	DynamicVector(const int& capacity = 1) : length{ 0 }, capacity{ capacity }
	{
		this->data = new TElem[capacity];
	};

	/// <summary>
	/// Constructs the DynamicVector
	/// </summary>
	/// <param name="v">the DynamicVector to copy</param>
	DynamicVector(const DynamicVector& v)
	{
		this->capacity = v.capacity;
		this->length = v.length;

		this->data = new TElem[this->capacity];
		for (int i = 0; i < this->length; i++)
			this->data[i] = v.data[i];
	};
	
	/// <summary>
	/// Overrides the plus operator to add a TElem to the DynamicArray
	/// </summary>
	/// <param name="vect">the DynamicVector to add to</param>
	/// <param name="elem">the element to add</param>
	/// <returns>The DynamicArray</returns>
	friend DynamicVector& operator+(DynamicVector& vect, const TElem& elem)
	{
		vect.add(elem);
		return vect;
	};

	/// <summary>
	/// Overrides the plus operator to add a TElem to the DynamicArray
	/// </summary>
	/// <param name="elem">the element to add</param>
	/// <param name="vect">the DynamicVector to add to</param>
	/// <returns>The DynamicArray</returns>
	friend DynamicVector& operator+(const TElem& elem, DynamicVector& vect)
	{
		vect.add(elem);
		return vect;
	};

	/// <summary>
	/// Overrides the plus equals operator to add a TElem to the DynamicArray
	/// </summary>
	/// <param name="elem">the element to add</param>
	/// <returns>The address of the DynamicArray</returns>
	DynamicVector& operator+=(const TElem& elem)
	{
		this->add(elem);
		return *this;
	};

	/// <summary>
	/// Overrides the equals operator to create a copy of a DynamicVector
	/// </summary>
	/// <param name="v">the DynamicVector to copy</param>
	/// <returns>The address of the new DynamicArray</returns>
	DynamicVector& operator=(const DynamicVector& v)
	{
		if (this == &v) return *this;

		this->capacity = v.capacity;
		this->length = v.length;

		delete[] this->data;
		this->data = new TElem[this->capacity];
		for (int i = 0; i < this->length; i++)
			this->data[i] = v.data[i];

		return *this;
	};

	/// <summary>
	/// Returns the element at the given index
	/// <param name="index">the index</param>
	/// </summary>
	TElem& operator[](int index) { return this->data[index]; }

	/// <summary>
	/// Adds an element to the DynamicVector and resizes if needed
	/// </summary>
	/// <param name="elem">the element to add</param>
	/// <returns>true</returns>
	void add(const TElem& elem)
	{
		if (this->length == this->capacity)
			this->resize();

		this->data[this->length++] = elem;
	};

	/// <summary>
	/// Removes an element from the DynamicVector
	/// </summary>
	/// <param name="elem">the element to remove</param>
	/// <returns>true, if the element was removed
	///			 false, otherwise</returns>
	bool remove(const TElem& elem)
	{
		for (int i = 0; i < this->length; i++)
		{
			if (this->data[i] == elem)
			{
				for (int j = i; j < this->length - 1; j++)
				{
					this->data[j] = this->data[j + 1];
				}

				this->length--;
				return true;
			}
		}

		return false;
	};
	
	/// <summary>
	/// Searches for an element in the DynamicVector
	/// </summary>
	/// <param name="elem">the element to find</param>
	/// <returns>true, if the element was found
	///			 false, otherwise</returns>
	bool search(const TElem& elem) const
	{
		for (int i = 0; i < this->length; i++)
			if (this->data[i] == elem)
				return true;

		return false;
	};

	/// <summary>
	/// Finds the index of an element in the DynamicVector
	/// </summary>
	/// <param name="elem">the element to find</param>
	/// <returns>the index, if the element was found
	///					-1, otherwise</returns>
	int indexOf(const TElem& elem) const
	{
		for (int i = 0; i < this->length; i++)
			if (this->data[i] == elem)
				return i;

		return -1;
	};

	/// <summary>
	/// Returns the size of the DynamicVector
	/// </summary>
	int size() const { return this->length; }

	/// <summary>
	/// Destructs the DynamicVector
	/// </summary>
	~DynamicVector()
	{
		delete[] this->data;
	};
};
