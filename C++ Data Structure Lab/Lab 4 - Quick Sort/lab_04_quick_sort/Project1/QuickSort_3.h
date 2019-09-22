/*
	Tran, Hoang

	CS A200
	Oct 7, 2017

	Lab 4
*/

#pragma once

void quickSort_3(int a[], int startIndex, int endIndex)
{
	// Pseudocode available in the lecture slides.
	if (startIndex < endIndex)
	{
		int pivot = partition_3(a, startIndex, endIndex);
		quickSort_3(a, startIndex, pivot - 1);
		quickSort_3(a, pivot + 1, endIndex);
	}
}

int partition_3(int a[], int startIndex, int endIndex)
{
	// PARTITION 3

	// show array
	cout << "\n----------------------------------";
	cout << "\n       ARRAY IS: ";
	print(a, startIndex, endIndex);

	int middle = (startIndex + endIndex) / 2;		 // choose the middle key as the pivot
	int pivot = a[middle];

	// show pivot	
	cout << "\n          PIVOT: " << pivot;

	swap(a[startIndex], a[middle]);			// swap pivot with first element

											// show pivot swapped	
	cout << "\n  PIVOT SWAPPED: ";
	print(a, startIndex, endIndex);
	cout << endl;

	/**************************************************************************
	Your implementation for the partition goes here.
	**************************************************************************/
	int h = startIndex;
	int k = h + 1;

	while (k <= endIndex)
	{
		if (a[k] <= pivot)
		{
			swap(a[h + 1], a[k]);
			++h;
			++k;
		}
		else
			++k;
	}

	swap(a[startIndex], a[h]);

	/**************************************************************************
		Display results.
	**************************************************************************/

	// show array after pass and after re-swapping pivot
	cout << "=> PASS/RE-SWAP: ";
	print(a, startIndex, endIndex);
	cout << endl;

	/**************************************************************************
	Replace the value 0 with the variable you need to return.
	**************************************************************************/
	
	return h;		
}


