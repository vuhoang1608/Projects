#include "DArray.h"

DArray::DArray( )
{
    capacity = 50;
	a = new int[capacity];	
	numOfElements = 0;
}

DArray::DArray(int newCapacity) 
{
	capacity = newCapacity;
    a = new int[capacity];
	numOfElements = 0;	 
}

DArray::DArray(const DArray& otherArray)
{
	capacity = otherArray.capacity;
	numOfElements = otherArray.numOfElements;

	a = new int[capacity];

	for (int i = 0; i < numOfElements; ++i)
		a[i] = otherArray.a[i];
}

void DArray::addElement(int newElement)
{
    if (numOfElements >= capacity)
    {
        cerr << "Attempt to exceed capacity in DArray.\n";
        exit(0); 
    }
	else
	{
		a[numOfElements] = newElement;
		++numOfElements;
	}
}

int DArray::getNumOfElements() const
{
	return numOfElements;
}

void DArray::printArray() const
{
	if (numOfElements == 0)
		cerr << "Array is empty." << endl;
	else
	{
		for (int i = 0; i < numOfElements; ++i)
			cout << a[i] << " ";
		cout << endl;
	}
}

DArray::~DArray( )
{
    delete [] a; 
	a = nullptr;	 
}

DArray& DArray::operator=(const DArray& otherArray)
{
	if (&otherArray != this)
	{
		if (capacity != otherArray.capacity)
		{
			delete[] a;
			a = new int[otherArray.capacity];
			capacity = otherArray.capacity;
		}

		numOfElements = otherArray.numOfElements;

		for (int i = 0; i < numOfElements; ++i)
			a[i] = otherArray.a[i];
	}
	else
	{
		cerr << "Attempted assignment to itself.";
	}

	return *this;
}

