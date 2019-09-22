/*
Tran, Hoang
Le, Duy
Nguyen, Anh

CS A200
Sep 07, 2017

Lab 2
*/

#include "AnyList.h"

ostream& operator<< (ostream& out, const AnyList& list)
{
	if (list.first == nullptr)
		out << "List is empty" << endl;
	else
	{
		Node* current = list.first;
		while (current != nullptr)
		{
			out << current->getData() << " ";
			current = current->getLink();
		}
	}
	return out;
}

AnyList::AnyList()
{
	first = nullptr;
	last = nullptr;
	count = 0;
}

AnyList::AnyList(const AnyList& list)
{
	first = nullptr;
	last = nullptr;
	count = 0;

	if (list.count != 0)
	{
		Node* current = list.first;

		while (current != nullptr)
		{
			insertBack(current->getData());
			current = current->getLink();
		}
	}
}

void AnyList::insertBack(int value)
{
	Node* newNode = new Node(value, nullptr);

	if (count == 0)
	{
		first = newNode;
	}
	else
	{
		last->setLink(newNode);
	}
	
	last = newNode;
	++count;
}

AnyList& AnyList::operator=(const AnyList& list)
{
	if (&list != this)
	{
		destroyList();
		if (list.first != nullptr)
		{
			Node* current = list.first;
			while (current != nullptr)
			{
				insertBack(current->getData());
				current = current->getLink();
			}
		}
	}
	else
		cerr << "Attempted assignment to itself.";

	return *this;
}

void AnyList::append(const AnyList& list)
{
	if (list.first != nullptr)
	{
		Node* current = list.first;
		while (current != nullptr)
		{
			insertBack(current->getData());
			current = current->getLink();
		}
	}
}

void AnyList::destroyList()
{
	Node* temp = nullptr;
	
	while (first != nullptr)
	{
		temp = first;
		first = first->getLink();
		delete temp;
		temp = nullptr;
	}

	last = nullptr;
	count = 0;
}

AnyList::~AnyList()
{
	destroyList();
}