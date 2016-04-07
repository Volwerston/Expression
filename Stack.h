#pragma once

#include <iostream>

using namespace std;

class Stack;

class Element
{
	char data;
	Element* next;
	friend class Stack;
public:
	Element(char _dat) : data(_dat), next(nullptr) {}
	int getData() const { return data; }
};

class Stack
{
	Element* first;
	Element* last;
public:
	Stack() : first(nullptr), last(nullptr) {}

	bool isEmpty()
	{
		return (first == nullptr && last == nullptr);
	}

	void push(const char& data)
	{
		Element* elmnt = new Element(data);
		if (isEmpty())
		{
			first = last = elmnt;
		}
		else
		{
			last->next = elmnt;
			last = elmnt;
			last->next = nullptr;
		}
	}

	void pop(char& data)
	{
		if (isEmpty())
		{
			cout << "The stack is empty" << endl;
		}
		else if (first == last)
		{
			data = first->getData();
			delete[] last;
			first = last = nullptr;
		}
		else
		{
			Element* elmnt = first;
			while (elmnt->next != last)
			{
				elmnt = elmnt->next;
			}
			data = last->getData();
			delete[] last;
			last = elmnt;
			last->next = nullptr;
		}
	}

	void print()
	{
		if (isEmpty())
		{
			cout << "The stack is empty";
		}
		else
		{
			Element* elmnt = first;
			while (elmnt != 0)
			{
				cout << elmnt->getData() << " ";
				elmnt = elmnt->next;
			}
		}
		cout << endl;
	}

	~Stack()
	{
		int data;
		Element* elmnt = first;
		Element* tech;
		while (elmnt != 0)
		{
			tech = elmnt;
			elmnt = elmnt->next;
			delete[] tech;
		}
	}
};