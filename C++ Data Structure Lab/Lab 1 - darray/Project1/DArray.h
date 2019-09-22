#ifndef DARRAY_H
#define DARRAY_H

#include <iostream>
using namespace std;

class DArray
{
public:
    DArray( );
	DArray(const DArray&);
    DArray(int newCapacity);

    void addElement(int newElement);

	int getNumOfElements() const;

	void printArray() const;

	DArray& operator=(const DArray&);
	
	~DArray();

	// Declaration function emptyArray
	void emptyArray();

	// Declaration function append
	void append(const DArray& other);

	// Declaration move constructor
	DArray(DArray&& other);

	// Declaration move assignment operator
	DArray& operator=(DArray&& other);

private:
    int *a;					//will point to an array of integers
    int capacity;			//capacity of the array
    int numOfElements;		//total number of elements in the array

};

#endif