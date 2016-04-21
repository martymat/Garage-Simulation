#ifndef Stack_h
#define Stack_h
#include <string>
#include<iostream>
#include <cstdlib>

template<class StackType>

class Stack {

public:
	Stack(int MaxStackSize = 10);
	~Stack() { delete[] stack; }
	bool IsEmpty() const { return top == -1; }
	bool IsFull() const { return top == MaxTop; }
	StackType Top() const;
	void push(const StackType & vehicle);
	void pop();
	int numberOfSpacesAvail() { return 9 - top; }
	bool search(const StackType vehicle);
	void display();
private:
	int top;
	int MaxTop;
	StackType *stack;
};


template<class StackType>
Stack<StackType>::Stack(int MaxStackSize)
{
	MaxTop = MaxStackSize - 1;
	stack = new StackType[MaxStackSize];
	top = -1;
}

template<class StackType>
StackType Stack<StackType>::Top() const
{
	if (IsEmpty())
		throw logic_error("Top fails: Stack is empty");
	return stack[top];
}

template<class StackType>
void Stack<StackType>::push(const StackType & vehicle)
{
	if (IsFull()) throw logic_error("Push fails: full Stack");
	stack[++top] = vehicle;
}

template<class StackType>
void Stack<StackType>::pop()
{
	if (IsEmpty()) {
		throw logic_error("Pop fails: Stack is empty");
	};
	top--;
}

template<class StackType>
bool Stack<StackType>::search(const StackType vehicle)
{
	bool found = false;
	for (int i = 0; i <= top; i++)
	{
		if (vehicle.plate == stack[i].plate)
		{
			found = true;
		}
	}

	return found;

}


#include "Garage.h"
#endif