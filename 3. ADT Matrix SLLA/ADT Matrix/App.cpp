#include <iostream>

#include "Matrix.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;

int main()
{
	testAll();
	testAllExtended();

	cout << "Test End" << endl;
	system("pause");

	return 0;
}
