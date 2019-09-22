/*
	Tran, Hoang

	CS A200
	Oct 7, 2017

	Lab 4
*/

/***************************************************************

	Quick Sort 
	
	Implementation from example 2 and 3 from the slides.

***************************************************************/

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

void quickSort_2(int[], int, int);
int partition_2(int[], int, int);

void quickSort_3(int[], int, int);
int partition_3(int[], int, int);

void processArray(int[], int);
void swap(int&, int&);
void print(const int[], int);
void print(const int[], int, int);
void test_quickSort(int a[], int numOfElem);

#include "QuickSort_2.h"
#include "QuickSort_3.h"
#include "Testing.h"

const int LARGE_CAP = 100;


int main()
{
	{
		// array from the slides
		int a[] = { 16, -3, 42, 101, -1, -17, 72, -31, 9 };
		int numOfElem = 9;
		processArray(a, numOfElem);
	}

	cout << "\n===================================================\n\n";

	{
		// random array
		int numOfElem = LARGE_CAP;
		int a[LARGE_CAP];

		srand(static_cast<unsigned int>(time(0)));			
		for (int i = 0; i < numOfElem; ++i)
			a[i] = 1 + rand() % (numOfElem * 10);

		processArray(a, numOfElem);
	}

	cout << endl << endl;
	system("Pause");
	return 0;
}

void processArray(int a[], int numOfElem)
{
	cout << "ORIGINAL ARRAY: ";
	print(a, numOfElem);
	cout << endl;

	test_quickSort(a, numOfElem);

	cout << "\n---------------------------------------------------\n\n";

	cout << "SORTED ARRAY: ";
	print(a, numOfElem);
	cout << endl;
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void print(const int a[], int numOfElem)
{
	for (int i = 0; i < numOfElem; ++i)
		cout << a[i] << " ";
}

void print(const int a[], int startIndex, int endIndex)
{
	for (int i = startIndex; i <= endIndex; ++i)
		cout << a[i] << " ";
}