#include "DArray.h"

#include <iostream>
using namespace std;

void populateArray(HeapSort& arr, int numOfElem, int start)
{
	for (int i = 0; i < (numOfElem + start); i += 10)
		arr.addElement(i + numOfElem);
}

int main()
{
	cout << "============== TESTING INSERT MAX ============" << endl;
	HeapSort a;
	a.insertMax(10);
	a.print();
	a.insertMax(14);
	a.print();
	a.insertMax(22);
	a.print();
	a.insertMax(35);
	a.print();
	a.insertMax(30);
	a.print();
	a.insertMax(7);
	a.print();
	a.insertMax(15);
	a.print();

	cout << "============== TESTING INSERT MIN ============" << endl;
	HeapSort b;
	b.insertMin(10);
	b.print();
	b.insertMin(9);
	b.print();
	b.insertMin(6);
	b.print();
	b.insertMin(4);
	b.print();
	b.insertMin(5);
	b.print();
	b.insertMin(8);
	b.print();
	b.insertMin(7);
	b.print();

	cout << "============== TESTING REMOVE MAX ============" << endl;
	a.removeMax();
	a.print();
	a.removeMax();
	a.print();
	a.removeMax();
	a.print();
	a.removeMax();
	a.print();
	a.removeMax();
	a.print();
	a.removeMax();
	a.print();

	cout << "============== TESTING REMOVE MIN ============" << endl;
	b.removeMin();
	b.print();
	b.removeMin();
	b.print();
	b.removeMin();
	b.print();
	b.removeMin();
	b.print();
	b.removeMin();
	b.print();
	b.removeMin();
	b.print();

	cout << "============== TESTING HEAP SORT ============" << endl;
	HeapSort c;
	c.addElement(28);
	c.addElement(35);
	c.addElement(12);
	c.addElement(37);
	c.addElement(5);
	c.addElement(45);
	c.addElement(21);
	c.addElement(18);
	cout << "Array before sorting: ";
	c.print();
	c.MaxSort();
	cout << "\nArray after Max Sort: ";
	c.print();

	cout << endl;
	system("Pause");
	return 0;
}

