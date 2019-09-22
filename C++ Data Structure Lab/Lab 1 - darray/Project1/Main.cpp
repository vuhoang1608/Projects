#include "DArray.h"

#include <iostream>
using namespace std;

const int START_10 = 10;
const int START_1000 = 1000;

void populateArray(DArray& arr, int numOfElem, int start);

#include "Test_Append.h"
#include "Test_Move_Constructor.h"
#include "Test_Move_Assign_Opr.h"

int main()
{
	testAppend();
	
	cout << "\n=========================================\n";

	testMoveConstructor();

	cout << "\n=========================================\n";

	testMoveAssignOpr();

	cout << endl;
	system("Pause");
    return 0;
}

void populateArray(DArray& arr, int numOfElem, int start)
{
	for (int i = start; i < (numOfElem + start); ++i)
		arr.addElement(i + numOfElem);
}
