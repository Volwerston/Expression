#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include "Expression.h"
#include "Stack.h"

using namespace std;

template <class T>
string toString(const T& t)
{
	ostringstream oStream;
	oStream << t;
	return oStream.str();
}

bool toDouble(const string& st, double& d)
{
	istringstream iStream(st);

	return (iStream >> d) ? true : false;
}

bool isHigherOrSame(char input, char top)
{
	bool isHighOrSame = false;

	switch (input)
	{
	case '+':
	case '-':
		if (top == '+' || top == '-' || top == '/' || top == '*' || top == '^')
		{
			isHighOrSame = true;
		}
		break;
	case '/':
	case '*':
		if (top == '*' || top == '/' || top == '^')
		{
			isHighOrSame = true;
		}
		break;
	case '^':
		if (top == '^')
		{
			isHighOrSame = true;
		}
		break;
	}

	return isHighOrSame;
}

Expression::Expression(string _inf)
	:infix(_inf)
{
	convertToPostfix();
}

void Expression::convertToPostfix()
{
	Stack stack;

	stack.push('(');
	postfix = "";

	string st = infix;

	st += ")";

	for (size_t i = 0; i < st.size(); ++i)
	{
		switch (st[i])
		{
		case '(':
			stack.push('(');
			break;
		case ')':
			postfix += " ";
			char data;
			stack.pop(data);

			while (data != '(')
			{
				postfix += data;
				postfix += " ";

				stack.pop(data);
			}
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':

			postfix += " ";

			stack.pop(data);

			while (isHigherOrSame(st[i], data) && data != '(')
			{
				postfix += data;
				postfix += " ";
				stack.pop(data);
			}

			stack.push(data);
			stack.push(st[i]);

			break;
		case ' ':

			break;
		case 's':
			if (st[i + 1] == 'i' && st[i + 2] == 'n')
			{
				int count = i + 4;
				string _sin;
				while (st[count] != ')')
				{
					_sin += st[count];
					++count;
				}

				i = count;

				double doubleStr;
				toDouble(_sin, doubleStr);

				double res = sin(doubleStr);

				postfix += toString(res);
				postfix += " ";
			}
			break;
		case 'c':
			if (st[i + 1] == 'o' && st[i + 2] == 's')
			{
				int count = i + 4;
				string _cos;
				while (st[count] != ')')
				{
					_cos += st[count];
					++count;
				}

				i = count;

				double doubleStr;
				toDouble(_cos, doubleStr);

				double res = cos(doubleStr);

				postfix += toString(res);
				postfix += " ";
			}
			else if (st[i + 1] == 't' && st[i + 2] == 'g')
			{
				int count = i + 4;
				string _ctg;
				while (st[count] != ')')
				{
					_ctg += st[count];
					++count;
				}

				i = count;

				double doubleStr;
				toDouble(_ctg, doubleStr);

				double res = double(1) / tan(doubleStr);

				postfix += toString(res);
				postfix += " ";
			}
			break;
		case 't':
			if (st[i + 1] == 'g')
			{
				int count = i + 3;
				string _tg;
				while (st[count] != ')')
				{
					_tg += st[count];
					++count;
				}

				i = count;

				double doubleStr;
				toDouble(_tg, doubleStr);

				double res = tan(doubleStr);

				postfix += toString(res);
				postfix += " ";
			}
			break;
		case 'l':
			if (st[i + 1] == 'o' || st[i + 2] == 'g')
			{
				string base;
				string num;
				int count = i + 4;

				while (st[count] != '>')
				{
					base += st[count];
					++count;
				}

				count += 2;

				while (st[count] != '>')
				{
					num += st[count];
					++count;
				}

				i = count;

				double _base;
				toDouble(base, _base);

				double _num;
				toDouble(num, _num);

				double res = double(log2(_num)) / log2(_base);

				postfix += toString(res);

				postfix += " ";
			}
			break;
		default:
			postfix += st[i];
			break;
		}
	}
}

double Expression::getResult() const
{
	bool finish = false;
	bool actionDone = false;
	double result = 0;
	string st = postfix;

	while (!finish)
	{
		int operPos = st.find_first_of("*+-/^");

		if (operPos == string::npos)
		{
			if (!actionDone)
			{
				toDouble(postfix, result);
			}

			break;
		}
		else
		{
			string sub1, sub2;

			int start = operPos - 1;

			while (st[start] == ' ')
			{
				--start;
			}

			while (st[start] != ' ')
			{
				sub2 = st[start] + sub2;
				--start;
			}

			while (st[start] == ' ')
			{
				--start;
			}

			while (start >= 0)
			{
				if (st[start] != ' ')
				{
					sub1 = st[start] + sub1;
					--start;
				}
				else
				{
					break;
				}
			}

			double arg1, arg2;

			toDouble(sub1, arg1);
			toDouble(sub2, arg2);

			if (st[operPos] == '*')
			{
				result = arg1*arg2;
			}
			else if (st[operPos] == '/')
			{
				result = double(arg1) / arg2;
			}
			else if (st[operPos] == '+')
			{
				result = arg1 + arg2;
			}
			else if (st[operPos] == '-')
			{
				result = arg1 - arg2;
			}
			else if (st[operPos] == '^')
			{
				result = pow(arg1, arg2);
			}

			st.erase(start + 1, operPos - start);
			st.insert(start + 1, toString(result));

			actionDone = true;
		}
	}

	return result;
}

istream& operator>>(istream& in, Expression& exp)
{
	getline(in, exp.infix);
	exp.convertToPostfix();
	return in;
}

ostream& operator<<(ostream& out, const Expression& exp)
{
	out << exp.postfix;

	return out;
}

string Expression::getPostfix() const
{
	return postfix;
}

string Expression::getInfix() const
{
	return infix;
}