#ifndef TEST_APPEND_H
#define TEST_APPEND_H

#include "DArray.h"

#include <iostream>
using namespace std;

void append(DArray& arr1, const DArray& arr2)
{
	cout << "arr1: ";
	arr1.printArray();
	cout << "arr2: ";
	arr2.printArray();
	arr1.append(arr2);
	cout << "arr1 is now: ";
	arr1.printArray();
}

void testAppend()
{
	cout << "TEST append...\n\n";

	{
		cout << "arr1 has more elements than arr2...\n";
		DArray arr1(10), arr2(10);
		int numOfElem1 = 6, numOfElem2 = 4;

		populateArray(arr1, numOfElem1, START_10);
		populateArray(arr2, numOfElem2, START_1000);
		append(arr1, arr2);
	}

	{
		cout << "\narr2 is empty...\n";
		DArray arr1(10), arr2(10);
		int numOfElem1 = 5, numOfElem2 = 0;	

		populateArray(arr1, numOfElem1, START_10);
		populateArray(arr2, numOfElem2, START_1000);
		append(arr1, arr2);
	}

	{
		cout << "\narr1 is empty...\n";
		DArray arr1(10), arr2(10);
		int numOfElem1 = 0, numOfElem2 = 6;

		populateArray(arr1, numOfElem1, START_10);
		populateArray(arr2, numOfElem2, START_1000);
		append(arr1, arr2);
	}

	{
		cout << "\narr1 does not have enugh space...\n";
		DArray arr1(10), arr2(10);
		int numOfElem1 = 7, numOfElem2 = 8;

		populateArray(arr1, numOfElem1, START_10);
		populateArray(arr2, numOfElem2, START_1000);
		append(arr1, arr2);
	}
}

#endif
