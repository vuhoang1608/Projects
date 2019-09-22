/*
Tran, Hoang

CS A200
Sep 20, 2017

Lab 3
*/

#include <iostream>

using namespace std;

void printArray(int a[], int capacity)
{
	for (int i = 0; i < capacity; ++i)
		cout << a[i] << " ";
	cout << endl;
}

void radixSort(int a[], int capacity, int numOfDigit)
{
	int *b = new int[capacity];

	cout << "\nArray before sorting: ";
	printArray(a, capacity);	

	//The sorting process	
	int j = 0;
	int exp = 1;
	for (int n = 1; n <= numOfDigit; ++n) // This statement has the running time of O(n * k)
	{
		for (int i = 0; i <= 9; ++i)
		{
			for (int numOfElem = 0; (j < capacity) && (numOfElem < capacity); ++numOfElem) 
				// This statement has the running time of O(n)
			{
				if (n % 2 != 0)
				{
					if ((a[numOfElem] / exp) % 10 == i)
					{
						b[j] = a[numOfElem];
						++j;
					}
				}
				else
				{
					if ((b[numOfElem] / exp) % 10 == i)
					{
						a[j] = b[numOfElem];
						++j;
					}
				}				
			}
		}
		j = 0;
		exp *= 10;

		//Print sorted array after each iteration
		cout << "\n* Array after " << n << " iteration: ";
		if(n % 2 != 0)
			printArray(b, capacity);
		else
			printArray(a, capacity);
	}
}

int main()
{
	cout << "==================== TEST 1 ====================" << endl;
	int a[10] = {560,222,306,654,763,899,959,749,588,677};	
	radixSort(a, 10, 3);

	cout << "\n==================== TEST 2 ====================" << endl;
	int b[7] = {56,18,27,95,80,76,42};
	radixSort(b, 7, 2);

	cout << "\n==================== TEST 3 ====================" << endl;
	int c[8] = {1345,8045,7845,4329,9854,5507,5487,2340};
	radixSort(c, 8, 4);

	cout << "\n==================== TEST 4 ====================" << endl;
	int d[8] = {12345,56410,38965,78612,95021,80506,75024,35860};
	radixSort(d, 8, 5);
	
	cout << endl;
	system("Pause");
	return 0;
}