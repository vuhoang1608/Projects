#include "DArray.h"

HeapSort::HeapSort()
{
	capacity = 50;
	a = new int[capacity];
	noe = 0;
}

HeapSort::HeapSort(const HeapSort& other)
{
	capacity = other.capacity;
	a = new int[capacity];
	noe = other.noe;

	if (other.noe != 0)
	{
		for (int i = 0; i < other.noe; ++i)
			a[i] = other.a[i];
	}
}

HeapSort& HeapSort::operator=(const HeapSort& other)
{
	if (this != &other)
	{
		if (capacity != other.capacity)
		{
			delete[] a;
			capacity = other.capacity;
			a = new int[capacity];
		}
		
		noe = other.noe;

		if (other.noe != 0)
		{
			for (int i = 0; i < other.noe; ++i)
				a[i] = other.a[i];
		}
	}
	else
		cerr << "Attempted assignment to itself.";

	return *this;
}

HeapSort::HeapSort(HeapSort&& other)
{
	capacity = other.capacity;
	noe = other.noe;
	a = other.a;

	other.capacity = 0;
	other.noe = 0;
	other.a = nullptr;
}

HeapSort& HeapSort::operator=(HeapSort&& other)
{
	if (this != &other)
	{
		delete[] a;

		capacity = other.capacity;
		noe = other.noe;
		a = other.a;

		other.capacity = 0;
		other.noe = 0;
		other.a = nullptr;
	}
	else
		cerr << "Attempted assignment to itself";

	return *this;
}

HeapSort::~HeapSort()
{
	delete[] a;
	a = nullptr;
}

//HeapSort::HeapSort()
//{
//	capacity = 50;
//	a = new int[capacity];
//	noe = 0;
//}
//
//HeapSort::HeapSort(const HeapSort& other)
//{
//	capacity = other.capacity;
//	noe = other.noe;
//
//	a = new int[capacity];
//
//	if (other.noe != 0)
//	{
//		for (int i = 0; i < other.noe; ++i)
//			a[i] = other.a[i];
//	}
//}
//
//HeapSort& HeapSort::operator=(const HeapSort& other)
//{
//	if (this != &other)
//	{
//		if (other.capacity != capacity)
//		{
//			delete[] a;
//			a = new int[other.capacity];
//			capacity = other.capacity;
//		}
//
//		noe = other.noe;
//
//		if (other.noe != 0)
//		{
//			for (int i = 0; i < other.noe; ++i)
//				a[i] = other.a[i];
//		}
//	}
//	else
//	{
//		cerr << "Attempted assignment to itself";
//	}
//
//	return *this;
//}
//
//HeapSort::HeapSort(HeapSort&& other) //move constructor
//{
//	a = other.a;
//	capacity = other.capacity;
//	noe = other.noe;
//
//	other.a = nullptr;
//	other.capacity = 0;
//	other.noe = 0;
//}
//
//HeapSort& HeapSort::operator=(HeapSort&& other) //move assignment operator
//{
//	if (this != &other)
//	{
//		delete[] a;
//
//		a = other.a;
//		capacity = other.capacity;
//		noe = other.noe;
//
//		other.a = nullptr;
//		other.capacity = 0;
//		other.noe = 0;
//	}
//	else
//	{
//		cerr << "Attempt assignment to itself";
//	}
//
//	return *this;
//}
//
//HeapSort::~HeapSort()
//{
//	delete[] a;
//	a = nullptr;
//}
//
void HeapSort::print() const
{
	if (noe != 0)
	{
		for (int i = 0; i < noe; ++i)
			cout << a[i] << " ";
	}
	else
		cout << "Array is empty";
	cout << endl;
}
