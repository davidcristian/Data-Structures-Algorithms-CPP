#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include "MultiMap.h"
#include "MultiMapIterator.h"

using namespace std;

int main()
{
	testAll();
	testAllExtended();
	cout << "End" << endl;
	system("pause");

	return 0;
}
