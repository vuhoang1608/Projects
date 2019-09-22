/*
Tran, Hoang

CS A200
August 28, 2017

Lab 1
*/

#include "DArray.h"

// Definition function emptyArray
void DArray::emptyArray()
{
	numOfElements = 0;
}

// Definition function appendArray
void DArray::append(const DArray& other)
{
	if (other.capacity != 0)
	{
		if (capacity < (numOfElements + other.numOfElements))
		{
			capacity = numOfElements + other.numOfElements;
			int *temp = new int[capacity];

			for (int i = 0; i < numOfElements; ++i)
				temp[i] = a[i];
			
			delete[] a;
			a = temp;
		}

		for (int i = 0; i < other.numOfElements; ++i)
		{
			addElement(other.a[i]);
		}
	}
}

// Definition move constructor
DArray::DArray(DArray&& other)
{
	a = other.a;
	numOfElements = other.numOfElements;
	capacity = other.capacity;

	other.a = nullptr;
	other.numOfElements = 0;
	other.capacity = 0;
}

// Definition move assignment operator
DArray& DArray::operator=(DArray&& other)
{
	if (this != &other)
	{
		delete[] a;
		a = other.a;
		numOfElements = other.numOfElements;
		capacity = other.capacity;

		other.a = nullptr;
		other.numOfElements = 0;
		other.capacity = 0;
	}

	return *this;
}