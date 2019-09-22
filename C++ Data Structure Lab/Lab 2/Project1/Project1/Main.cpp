#include "AnyList.h"

using namespace std;

//void AnyList::print() const
//{
//	if (first != nullptr)
//	{
//		Node* current = first;
//
//		while (current != nullptr)
//		{
//			cout << current->getData() << " ";
//			current = current->getLink();
//		}
//	}
//	else
//		cout << "Empty list.";
//}

void testing(AnyList& myList, AnyList& yourList)
{
	cout << "\nMy list   : ";
	cout << myList;
	cout << "\nYour list : ";
	cout << yourList;
	myList.append(yourList);
	cout << "\nAfter appending: " << endl;
	cout << "My list   : ";
	cout << myList;
	cout << "\nYour list : ";
	cout << yourList;
	cout << endl;
	myList.destroyList();
	yourList.destroyList();
}

int main()
{
	cout << "Testing append function" << endl;
	cout << "------------------------------" << endl;
	AnyList myList;
	AnyList yourList;

	//Test 1
	cout << "\nTEST 1: " << endl;

	for (int i = 1; i <= 5; ++i)
	{
		myList.insertBack(i);
	}
		
	for (int i = 10; i <= 20; i += 2)
	{
		yourList.insertBack(i);
	}
		
	testing(myList, yourList);

	//Test 2
	cout << "\nTEST 2: " << endl;
	
	for (int i = 10; i <= 20; i += 2)
	{
		yourList.insertBack(i);
	}

	testing(myList, yourList);

	//Test 3
	cout << "\nTEST 3: " << endl;

	for (int i = 1; i <= 5; ++i)
	{
		myList.insertBack(i);
	}

	testing(myList, yourList);

	cout << "Testing assignment operator: " << endl;
	for (int i = 1; i <= 5; ++i)
	{
		myList.insertBack(i);
	}
	yourList = myList;
	cout << "My list: " << myList << endl;
	cout << "Your list: " << yourList << endl;

	cout << "\nTesting copy constructor: " << endl;
	AnyList otherList(myList);
	cout << "Other list: " << otherList;

	cout << endl;
	system("Pause");
	return 0;
}

