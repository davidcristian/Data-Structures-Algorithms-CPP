#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

#define INITIAL_CAPACITY 16
#define CAPACITY_SCALE 2

template <class T>
class stack
{
private:
	T* data;

	int capacity;
	int size;

	void resize()
	{
		int oldCapacity = this->capacity;
		this->capacity *= CAPACITY_SCALE;

		T* newData = new T[this->capacity];

		for (int i = 0; i < oldCapacity; i++)
			newData[i] = this->data[i];

		delete[] this->data;
		this->data = newData;
	}

public:
	stack() { this->size = 0; this->capacity = INITIAL_CAPACITY; this->data = new T[this->capacity]; }
	~stack() { delete[] this->data; }

	void clear() { delete[] this->data; this->size = 0; this->capacity = INITIAL_CAPACITY; this->data = new T[this->capacity]; }
	bool empty() { return this->size == 0; }

	void push(T elem) { if (this->size == this->capacity) this->resize(); this->data[this->size++] = elem; }
	T pop() { return this->data[this->size-- - 1]; }
	T top() { return this->data[this->size - 1]; }
};

class Node
{
public:
	TComp data;
	Node* left;
	Node* right;
	int numToleft;

	Node() : data{ NULL_TCOMP }, left{ nullptr }, right{ nullptr }, numToleft{ 0 } { }
	Node(TComp data, Node* left, Node* right, int numToleft) : data{ data }, left{ left }, right{ right }, numToleft{ numToleft } { }
};

class SortedIndexedList
{
private:
	//DO NOT CHANGE THIS PART
	friend class ListIterator;

	Relation relation;
	Node* root;
	int length;

	void destroyTree(Node* node);

public:
	// constructor
	SortedIndexedList(Relation r);

	// returns the size of the list
	int size() const;

	//checks if the list is empty
	bool isEmpty() const;

	// returns an element from a position
	//throws exception if the position is not valid
	TComp getElement(int pos) const;

	// adds an element in the sortedList (to the corresponding position)
	void add(TComp e);

	// removes an element from a given position
	//returns the removed element
	//throws an exception if the position is not valid
	TComp remove(int pos);

	// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
	int search(TComp e) const;

	// returns an iterator set to the first element of the list or invalid if the list is empty
	ListIterator iterator();


	//removes all elements between two positions, start and end
	//throws exception if start or end is not valid
	void removeBetween(int start, int end);


	//destructor
	~SortedIndexedList();
};
