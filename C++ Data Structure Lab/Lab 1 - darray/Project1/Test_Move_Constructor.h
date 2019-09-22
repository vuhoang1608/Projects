#ifndef MOVE_CONSTRUCTOR_H
#define MOVE_CONSTRUCTOR_H

#include "DArray.h"

#include <iostream>
using namespace std;

void testMoveConstructor()
{
	cout << "TEST move assignment operator... "
		<< "Move data from arr2 into arr1.\n";

	{
		DArray arr2(10);
		int numOfElem2 = 4;
		populateArray(arr2, numOfElem2, START_10);

		DArray arr1 = move(arr2);
		cout << "\narr1 = ";		
		arr1.printArray();

		if (arr2.getNumOfElements() == 0)
			cout << "arr2 is empty (all elements have been moved.)\n";
		else
			cout << "ERROR: arr2 is not empty.\n";
	}

	{
		DArray arr2(10);
		int numOfElem2 = 0;
		populateArray(arr2, numOfElem2, START_10);

		DArray arr1 = move(arr2);
		cout << "\narr1 = ";
		arr1.printArray();

		if (arr2.getNumOfElements() == 0)
			cout << "arr2 is empty (all elements have been moved.)\n";
		else
			cout << "ERROR: arr2 is not empty.\n";
	}
	
	{
		DArray arr2(10);
		int numOfElem2 = 8;
		populateArray(arr2, numOfElem2, START_10);

		DArray arr1 = move(arr2);
		cout << "\narr1 = ";
		arr1.printArray();

		if (arr2.getNumOfElements() == 0)
			cout << "arr2 is empty (all elements have been moved.)\n";
		else
			cout << "ERROR: arr2 is not empty.\n";
	}
}

#endif
