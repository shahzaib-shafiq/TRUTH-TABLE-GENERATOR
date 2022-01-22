#include"StackClass.h"
bool IsOperator(char ElementRead)
{
	if (ElementRead == '^' || ElementRead == '|' || ElementRead == '~'
		|| ElementRead == '(' || ElementRead == ')')
	{
		return true;
	}
	else
	{
		return false;
	}
}
int PostfixEvaluation(string PostfixGiven)
{
	Stack stack(PostfixGiven.length());
	for (int i = 0; i < PostfixGiven.length(); i++)
	{
		if (isdigit(PostfixGiven[i]))
		{
			int Value = 0;
			Value = (int)(PostfixGiven[i] - '0');
			stack.Push(Value);
		}
		else
		{
			if (PostfixGiven[i] == '~')
			{
				int val1 = stack.POP();
				if (val1 == 1)
				{
					stack.Push(0);
				}
				else
				{
					stack.Push(1);
				}
			}
			else
			{
				int Result = 0;
				int val1 = stack.POP();
				int val2 = stack.POP();
				switch (PostfixGiven[i])
				{
				case '^':
					stack.Push(val1 * val2);
					break;
				case '|':
					Result = val1 + val2;
					if (Result >= 2)
					{
						stack.Push(1);
					}
					else
					{
						stack.Push(Result);
					}
					break;
				}
			}
		}
	}
	return stack.TopValue();
}
void Display(string Operands, int**& Array, int Rows, int Columns)
{
	system("COLOR 6F");
	cout << "\n\t\t\t\"Truth Table\"\n"
		<< "\t-------------------------------------------\n\t";
	for (int i = 0; i < Columns - 1; i++)
	{
		cout << "|  " << Operands[i] << "  ";
	}
	cout << "| Result |\n\t ";
	for (int k = 0; k < Columns; k++)
	{
		cout << "-------";
	}
	cout << "\n\t";
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			if (j == Columns - 1)
			{
				cout << "|    " << Array[i][j] << "   ";
			}
			else
			{
				cout << "|  " << Array[i][j] << "  ";
			}
		}
		cout << "|" << "\n\t ";
		for (int k = 0; k < Columns; k++)
		{
			cout << "-------";
		}
		cout << "\n\t";
	}
}
void TruthTableGenerator()
{
	
	string InputString = "\0", UniqueOperand = "\0";
	cout << "\n\t----------------<< Input >>----------------\n";
		cout << "\n\t----------------<< Symbols Used\n\tAND -----> ^\n\tOR -----> |\n\tNOT -----> ~\n"
		
			<< "\n\tPlease Enter the Expression\n\n\t";
	
	getline(cin, InputString);
	
	cout << "\t-------------------------------------------";
	bool validate = true;
	////////////////////////////////
	for (int i = 0; i < InputString.length(); i++)
	{
		if (!IsOperator(InputString[i]) && !isalpha(InputString[i]))
		{
			validate = false;
			break;
		}
	}
	if (!validate)
	{
		system("COLOR 4f");
		cout << "\n\t----------------<< Attention >>----------------\n"
			<< "\n\tProvided Expression is \"Invalid\"\n"
			<< "\n\t-------------------------------------------\n";
		cout	<< "\n\tPlease Enter the Expression\n\n\t";

		getline(cin, InputString);

	}
	else
	{
		bool check;
		for (int i = 0; i < InputString.length(); i++)
		{
			if (!IsOperator(InputString[i]))
			{
				check = false;
				for (int j = 0; j < UniqueOperand.length(); j++)
				{
					if (InputString[i] == UniqueOperand[j])
					{
						check = true;
						break;
					}
				}
				if (!check)
				{
					UniqueOperand += InputString[i];
				}
			}
		}
		int Rows = pow(2, UniqueOperand.length());
		int Columns = UniqueOperand.length() + 1;
		int** Table = new int* [Rows];
		for (int i = 0; i < Rows; i++)
		{
			Table[i] = new int[Columns];
			for (int j = 0; j < Columns; j++)
			{
				Table[i][j] = 0;
			}
		}
		int Binaryof = 0;
		for (int i = 0; i < Rows; i++)
		{
			Binaryof = i;
			for (int j = Columns - 2; j >= 0 && Binaryof != 0; j--)
			{
				Table[i][j] = Binaryof % 2;
				Binaryof /= 2;
			}
		}
		/////////////////////////////////////
		Stack StackCreated(InputString.length());
		StackCreated.ToPostfix(InputString);

			string Expression = "\0";
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < InputString.length(); j++)//postfix expression
			{
				for (int k = 0; k < UniqueOperand.length(); k++)
				{
					if (InputString[j] == UniqueOperand[k] || IsOperator(InputString[j]))
					{
						if (IsOperator(InputString[j]))
						{
							Expression += InputString[j];
							break;
						}
						else
						{
							Expression += to_string(Table[i][k]);
							break;
						}
					}
				}
			}
			Table[i][Columns - 1] = PostfixEvaluation(Expression);
			Expression = "\0";
		}
		Display(UniqueOperand, Table, Rows, Columns);
		for (int i = 0; i < Rows; i++)
		{
			delete[] Table[i];
		}
		delete[] Table;
		Table = nullptr;
	}
}

int main()
{
	TruthTableGenerator();
	system("pause>0");
	return 0;
}

