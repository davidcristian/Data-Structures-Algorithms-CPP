#include <iostream>
#include <crtdbg.h>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"

using namespace std;

int main()
{
	testAll();
	testAllExtended();

	cout << "Test end" << endl;

	if (_CrtDumpMemoryLeaks() == 1)
		printf("WARNING: Memory leaks were detected. See the Output tab for more information.\n");
	else
		printf("INFO: No memory leaks were detected. The program executed correctly.\n");

	return 0;
}
