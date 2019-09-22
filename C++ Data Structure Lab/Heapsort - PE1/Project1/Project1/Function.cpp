#include "DArray.h"

void HeapSort::addElement(int value)
{
	if (noe >= capacity)
	{
		cerr << "Attempt to exceed the capacity. \n";
		exit(0);
	}
	else
	{
		a[noe] = value;
		++noe;
	}
}

void HeapSort::insertMax(int element)
{
	addElement(element);

	int key = noe - 1;
	int parent, left, temp;
	bool isHeap = false;

	while (key > 0 && !isHeap)
	{
		parent = (key - 1) / 2;
		left = (parent * 2) + 1;

		if (a[key] > a[parent])
		{
			temp = a[key];
			a[key] = a[parent];
			a[parent] = temp;

			if (left != key && a[left] > a[parent])
			{
				temp = a[left];
				a[left] = a[parent];
				a[parent] = temp;
			}
		}
		else
			isHeap = true;

		key = parent;
	}
}

void HeapSort::insertMin(int element)
{
	addElement(element);

	int key = noe - 1;
	int parent, left, temp;
	bool isHeap = false;

	while (key > 0 && !isHeap)
	{
		parent = (key - 1) / 2;
		left = (parent * 2) + 1;

		if (a[key] < a[parent])
		{
			temp = a[key];
			a[key] = a[parent];
			a[parent] = temp;

			if (left != key && a[left] < a[parent])
			{
				temp = a[left];
				a[left] = a[parent];
				a[parent] = temp;
			}
		}
		else
			isHeap = true;

		key = parent;
	}
}

void HeapSort::removeMax()
{
	a[0] = a[noe - 1];
	--noe;

	int key = 0, larger = key, left, right, temp;
	bool isHeap = false;

	while (key < noe && !isHeap)
	{
		left = (key * 2) + 1;
		right = (key * 2) + 2;

		if (left < noe && a[left] > a[larger])
			larger = left;
		if (right < noe && a[right] > a[larger])
			larger = right;

		if (larger != key)
		{
			temp = a[key];
			a[key] = a[larger];
			a[larger] = temp;
			key = larger;
		}
		else
			isHeap = true;
	}
}

void HeapSort::removeMin()
{
	a[0] = a[noe - 1];
	--noe;

	int key = 0, smaller = key;
	int left, right, temp;
	bool isHeap = false;

	while (key < noe && !isHeap)
	{
		left = (key * 2) + 1;
		right = (key * 2) + 2;

		if (left < noe && a[left] < a[smaller])
			smaller = left;		
		if (right < noe && a[right] < a[smaller])
			smaller = right;

		if (smaller != key)
		{
			temp = a[key];
			a[key] = a[smaller];
			a[smaller] = temp;
			key = smaller;
		}
		else
			isHeap = true;
	}
}

void HeapSort::MaxSort()
{
	int left, right, temp, larger;

	for (int i = noe; i > 0; i /= 2)
	{
		for (int root = (noe - 2) / 2; root >= 0; --root)
		{
			larger = root;
			left = root * 2 + 1;
			right = root * 2 + 2;

			if (left < noe && a[left] > a[larger])
				larger = left;
			if (right < noe && a[right] > a[larger])
				larger = right;

			if (larger != root)
			{
				temp = a[root];
				a[root] = a[larger];
				a[larger] = temp;
			}
		}
	}
}


//int left, right, smaller, temp;
//for (int i = noe; i > 0; i /= 2)
//{
//	for (int root = 0; root <= (noe - 1) / 2; ++root)
//	{
//		smaller = root;
//		left = (root * 2) + 1;
//		right = (root * 2) + 2;
//		if (left < noe && a[left] < a[smaller])
//			smaller = left;
//		if (right < noe && a[right] < a[smaller])
//			smaller = right;

//		if (smaller != root)
//			swap(a[root], a[smaller]);
//	}
//}

