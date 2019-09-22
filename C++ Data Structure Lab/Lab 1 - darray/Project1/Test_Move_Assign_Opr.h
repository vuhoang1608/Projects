#ifndef TEST_MOVE_ASSIGN_OPER_H
#define TEST_MOVE_ASSIGN_OPER_H

void processArrays(DArray& arr1, DArray& arr2)
{
	cout << "\narr1: ";
	arr1.printArray();
	cout << "arr2: ";
	arr2.printArray();

	arr1 = move(arr2);
	cout << " => move from arr2 to arr1 (arr2 should be empty)...\n";
	cout << "arr1: ";
	arr1.printArray();
	cout << "arr2: ";
	arr2.printArray();
}

void testMoveAssignOpr()
{
	cout << "TEST move assignment operator...\n";

	{
		DArray arr1(10), arr2(10);
		int numOfElem1 = 6, numOfElem2 = 4;
		populateArray(arr1, numOfElem1, START_10);
		populateArray(arr2, numOfElem2, START_1000);
		processArrays(arr1, arr2);
	}

	{
		DArray arr1(10), arr2(10);
		int numOfElem1 = 5, numOfElem2 = 0;
		populateArray(arr1, numOfElem1, START_10);
		populateArray(arr2, numOfElem2, START_1000);
	}

	{
		DArray arr1(10), arr2(10);
		int numOfElem1 = 0, numOfElem2 = 6;
		populateArray(arr1, numOfElem1, START_10);
		populateArray(arr2, numOfElem2, START_1000);
	}

	{
		DArray arr1(10), arr2(10);
		int numOfElem1 = 7, numOfElem2 = 8;
		populateArray(arr1, numOfElem1, START_10);
		populateArray(arr2, numOfElem2, START_1000);
	}
}

#endif
