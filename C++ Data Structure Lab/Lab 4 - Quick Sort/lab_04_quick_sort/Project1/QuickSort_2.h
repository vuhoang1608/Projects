/*
	Tran, Hoang

	CS A200
	Oct 7, 2017

	Lab 4
*/

#pragma once

void quickSort_2(int a[], int startIndex, int endIndex)
{
	// Pseudocode available in the lecture slides.
	if (startIndex < endIndex)
	{
		int pivot = partition_2(a, startIndex, endIndex);
		quickSort_2(a, startIndex, pivot - 1);
		quickSort_2(a, pivot + 1, endIndex);
	}
}

int partition_2(int a[], int startIndex, int endIndex)
{
	// PARTITION 2

	// show array
	cout << "\n----------------------------------";
	cout << "\n       ARRAY IS: ";
	print(a, startIndex, endIndex);

	int middle = (startIndex + endIndex) / 2;	// choose the middle key as the pivot
	int pivot = a[middle];

	// show pivot	
	cout << "\n          PIVOT: " << pivot;

	swap(a[startIndex], a[middle]);		// swap pivot with first element

	cout << "\n  PIVOT SWAPPED: ";		// show pivot swapped	
	print(a, startIndex, endIndex);
	cout << endl;

	/**************************************************************************
		Your implementation for the partition goes here.	
	**************************************************************************/
	int h = startIndex + 1;
	int k = endIndex;

	while (h <= k)
	{
		while (a[h] <= pivot && h <= endIndex) 
			++h;

		while (a[k] > pivot)
			--k;

		if(k > h)
			swap(a[h], a[k]);
	}
	
	swap(a[startIndex], a[k]);

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

	return k;
}


