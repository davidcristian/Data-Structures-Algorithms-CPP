#include "SortedSet.h"
#include "SortedSetIterator.h"

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
SortedSet::SortedSet(Relation r)
{
	relation = r;
    length = 0;

	capacity = 32;
    data = new TComp[capacity];
}

/// <summary>
/// Complexity:
/// WC: Theta(2n)
/// BC: Theta(1)
/// AC: Theta(2n)
/// Total time complexity: O(2n)
/// </summary>
bool SortedSet::add(TComp elem)
{
    if (search(elem)) return false;

    if (length == capacity)
    {
        capacity *= 2;

        TComp* newData = new TComp[capacity];
        for (int i = 0; i < length; i++)
            newData[i] = data[i];
        
        delete[] data;
        data = newData;
    }

    int index = 0;
    for (int i = 0; i < length; i++)
    {
        if (relation(data[i], elem))
            index = i + 1;
        else
            break;
    }

    for (int i = length; i > index; i--)
        data[i] = data[i - 1];
    
    data[index] = elem;
    length++;

    return true;
}

/// <summary>
/// Complexity:
/// WC: Theta(n)
/// BC: Theta(n)
/// AC: Theta(n)
/// Total time complexity: Theta(n)
/// </summary>
bool SortedSet::remove(TComp elem)
{
    bool found = false;
    int left = 0;
    int right = length - 1;
    int mid;

    for (mid = (left + right) / 2; left <= right; mid = (left + right) / 2)
        if (data[mid] == elem)
        {
            found = true;
            break;
        }
        else if (relation(data[mid], elem))
            left = mid + 1;
        else
            right = mid - 1;
    if (found == false) return false;

    for (int i = mid; i < length - 1; i++)
        data[i] = data[i + 1];

    length--;
    return true;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
int SortedSet::getRange() const
{
    if (this->isEmpty()) return -1;
    return this->data[this->length - 1] - this->data[0];
}

/// <summary>
/// Complexity:
/// WC: Theta(n)
/// BC: Theta(1)
/// AC: Theta(log n)
/// Total time complexity: O(log n)
/// </summary>
bool SortedSet::search(TComp elem) const
{
    int left = 0;
    int right = length - 1;
    int mid;

    for (mid = (left + right) / 2; left <= right; mid = (left + right) / 2)
        if (data[mid] == elem)
            return true;
        else if (relation(data[mid], elem))
            left = mid + 1;
        else right = mid - 1;

    return false;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
int SortedSet::size() const
{
    return length;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
bool SortedSet::isEmpty() const
{
    return length == 0;
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
SortedSetIterator SortedSet::iterator() const
{
	return SortedSetIterator(*this);
}

/// <summary>
/// Complexity:
/// Theta(1)
/// </summary>
SortedSet::~SortedSet()
{
    delete[] data;
}
