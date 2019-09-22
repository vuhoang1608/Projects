#ifndef DARRAY_H
#define DARRAY_H

#include <iostream>
using namespace std;

class HeapSort
{
public:	
	HeapSort();
	HeapSort(const HeapSort&);
	HeapSort& operator=(const HeapSort&);

	HeapSort(HeapSort&& other);
	HeapSort& operator=(HeapSort&& other);
	~HeapSort();
	
	void print() const;
	void addElement(int value);

	void insertMax(int element);
	void insertMin(int element);

	void removeMax();
	void removeMin();

	void MaxSort();

private:
	int* a;
	int noe;
	int capacity;
};
#endif