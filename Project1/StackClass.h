#pragma once
//Class Name : Stack
#pragma once
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
class Stack
{
private:
	int* StackArray;
	int StackSize;
	int Top;
public:
	Stack(int Size)
	{
		StackSize = Size;
		StackArray = new int[StackSize];
		Top = -1;
	}
	bool IsFull()
	{
		return Top == StackSize - 1;
	}
	bool Push(int InputValue)
	{
		if (!IsFull())
		{
			Top++;
			StackArray[Top] = InputValue;
			return true;
		}
		else
		{
			return false;
		}

	}
	bool IsEmpty()
	{
		if (Top == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int POP()
	{
		int TobeReturned;
		if (!IsEmpty())
		{

			TobeReturned = StackArray[Top];
			Top--;
			return TobeReturned;
		}
		else
		{
			return 0;
		}
	}
	int TopValue()
	{
		if (!IsEmpty())
		{

			return StackArray[Top];
		}
		else
		{
			return false;
		}
	}
	int PrecedenceAssigned(char ElementRead)
	{
		if (ElementRead == '|')
		{
			return 1;
		}
		else if (ElementRead == '^')
		{
			return 2;
		}
		else if (ElementRead == '~')
		{
			return 3;
		}
		else if (ElementRead == '(')
		{
			return 4;
		}
		else
		{
			return 0;
		}
	}
	bool Precedence(char TopofStack, char ElementRead)
	{
		if (TopofStack == '(')
		{
			return false;
		}
		else if (PrecedenceAssigned(TopofStack) < PrecedenceAssigned(ElementRead))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	void ToPostfix(string& Expression)
	{
		Stack OperatorHolder(StackSize);
		string PostfixExpression = "\0";
		char ElementPoped = '\0';
		for (int i = 0; i < Expression.length(); i++)
		{
			if (isalpha(Expression[i]) || isdigit(Expression[i]))
			{
				PostfixExpression.append(1, Expression[i]);
			}
			else
			{
				while (!OperatorHolder.IsEmpty() && Precedence(OperatorHolder.TopValue(), Expression[i]))
				{
					ElementPoped = OperatorHolder.POP();
					PostfixExpression.append(1, ElementPoped);
				}
				if (Expression[i] != ')')
				{
					OperatorHolder.Push(Expression[i]);
				}
				else
				{
					ElementPoped = OperatorHolder.POP();
				}
			}
		}
		while (!OperatorHolder.IsEmpty())
		{
			ElementPoped = OperatorHolder.POP();
			PostfixExpression.append(1, ElementPoped);
		}
		Expression = PostfixExpression;
	}
	~Stack()
	{
		delete[]StackArray;
		StackArray = nullptr;
		Top = -1;
	}
};