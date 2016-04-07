#include <iostream> 
#include <string>

#include "Expression.h"

using namespace std;

bool test1()
{
	_CrtMemState c1, c2, c3;

	_CrtMemCheckpoint(&c1);

	{
		Expression test;
	}

	_CrtMemCheckpoint(&c2);

	return !_CrtMemDifference(&c3, &c1, &c2);
}

bool test2()
{
	Expression exp("(2+1)^(3-1)*15*cos(0)");

	bool passed = (exp.getResult() == 135 ? true : false);

	return passed;
}

bool test3()
{
	Expression exp("(9/3)*log<2><128> + 2^(1+1)");

	bool passed = (exp.getPostfix() == "9 3 /  7  * 2 1 1 +  ^ + " ? true : false);

		if (passed)
		{
			passed = (exp.getResult() == 25 ? true : false);
		}

	return passed;
}

int main()
{
	if (!test1())
	{ 
		cout << "Test 1 failed" << endl;
	}
	else if (!test2())
	{
		cout << "Test 2 failed" << endl;
	}
	else if (!test3())
	{
		cout << "Test 3 failed" << endl;
	}
	else
	{
		cout << "All tests succeeded" << endl;
	}

	system("pause");
	return 0;
}