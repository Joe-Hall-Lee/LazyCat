#include <iostream>
using namespace std;
#include "Stack.h"

/* 类模板不带异常捕获 */
// int main()
// {
// 	CharStack s1(2);
// 	DoubleStack s2(2);
// 	char ch;
// 	double d;

// 	s1.push('a');
// 	s1.push('b');
// 	// s1.push('c');

// 	ch = s1.pop();
// 	cout << ch << endl;
// 	ch = s1.pop();
// 	cout << ch << endl;

// 	s2.push(2.1);
// 	s2.push(3.0);

// 	d = s2.pop();
// 	cout << d << endl;
// 	d = s2.pop();
// 	cout << d << endl;
// 	return 0;
// }

/* 类模板带异常捕获 */
int main()
{
	CharStack s1(2);
	char ch;

	try
	{
		s1.push('a');
		s1.push('b');
		s1.push('c');
	}
	catch (CharStack::Full)
	{
		cout << "Stack Full!!" << endl;
	}

	try
	{
		ch = s1.pop();
		cout << ch << endl;
		ch = s1.pop();
		cout << ch << endl;
		ch = s1.pop();
		cout << ch << endl;
	}
	catch (CharStack::Empty)
	{
		cout << "Stack Empty!!" << endl;
	}

	return 0;
}