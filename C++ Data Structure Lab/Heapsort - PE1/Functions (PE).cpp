/*
	Tran, Hoang

	CS A200
	Oct 4, 2017

	Exam 102
*/

#include "HeapSort.h"

// Definition of move constructor
HeapSort::HeapSort(HeapSort&& other)
{
	noOfItems = other.noOfItems;
	heap = other.heap;

	other.noOfItems = 0;
	other.heap = nullptr;
}

// Definition of function removeMax
int HeapSort::removeMax()
{
	if (noOfItems == 0)
	{
		cout << "Heap is empty";
		return 0;
	}
	else if (noOfItems == 1)
	{
		--noOfItems;
		return heap[noOfItems];
	}
	else
	{
		swap(heap[0], heap[noOfItems - 1]);
		--noOfItems;

		if(noOfItems > 1)
			bubbleDown();

		return heap[noOfItems];
	}
}

// Definition of function swap
void HeapSort::swap(int& first, int& second) const
{
	int temp = first;
	first = second;
	second = temp;
}


// Definition of function bubbleDown
void HeapSort::bubbleDown() const
{
	int key = 0, larger = key, left = 0, right = 0;
	bool isLarger = false;

	while (key < (noOfItems / 2) && !isLarger)
	{
		left = (key * 2) + 1;
		right = (key * 2) + 2;

		if (left < noOfItems && heap[left] > heap[larger])
			larger = left;
		if (right < noOfItems && heap[right] > heap[larger])
			larger = right;

		if (larger != key)
		{
			swap(heap[key], heap[larger]);
			key = larger;
		}
		else
			isLarger = true;
	}
}