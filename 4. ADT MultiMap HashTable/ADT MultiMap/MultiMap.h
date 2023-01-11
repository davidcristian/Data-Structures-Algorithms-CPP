#pragma once

#include <vector>
#include <utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

#define INITIAL_CAPACITY 16
#define CAPACITY_SCALE 2

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;

#define MAX_LOAD 0.7
#define key first
#define val second

class Node
{
public:
	TElem tuple;
	Node* next;

	Node() : tuple(NULL_TELEM), next(nullptr) { };
	Node(TKey tKey, TValue tValue, Node* next) : tuple(pair<int, int>(tKey, tValue)), next(next) { };
};

class MultiMap
{
	friend class MultiMapIterator;

private:
	int capacity;
	int nrPairs;
	Node** hTable;

	void resize();
	int hash(TKey k) const;
	void release(Node* n);

public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;
	

	//descturctor
	~MultiMap();
};
