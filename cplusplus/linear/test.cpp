#include <iostream>
#include "linear.h"


using namespace std;


int main()
{
	v test1, test2;
	test1.x = 13.123;
	test1.y = -123.543;
	test1.z = 764.25;
	test2.x = -154.7;
	test2.y = -87.432;
	test2.z = 213.4;
	cout << add (test1, test2) << endl;
	cout << subtr (test1, test2) << endl;
	cout << mult (434.12, test1) << endl;
	cout << dot (test1, test2) << endl;
	cout << cross (test1, test2) << endl;
}
