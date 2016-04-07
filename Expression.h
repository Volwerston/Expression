#pragma once

#include <string>

using namespace std;

class Expression
{
	string infix;
	string postfix;
public:
	Expression(string = "");

	void convertToPostfix();

	string getInfix() const;
	string getPostfix() const;

	double getResult() const;

	friend istream& operator>>(istream&, Expression&);
	friend ostream& operator<<(ostream& out, const Expression&);
};