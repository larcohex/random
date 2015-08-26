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
	cout << v_add (test1, test2) << endl;
	cout << v_subtr (test1, test2) << endl;
	cout << v_mult (434.12, test1) << endl;
	cout << v_dot (test1, test2) << endl;
	cout << v_cross (test1, test2) << endl;
	cout << "\n\n\n\n" << endl;
	m mest1 (3, 3);
	m mest2 (3, 4);
	mest1[0][0] = 1;
	mest1[0][1] = 2;
	mest1[0][2] = 3;
	mest1[1][0] = 0;
	mest1[1][1] = 1;
	mest1[1][2] = 4;
	mest1[2][0] = 5;
	mest1[2][1] = 6;
	mest1[2][2] = 0;
	cout << mest1 << endl;
	mest2[0][0] = -3;
	mest2[0][1] = -1;
	mest2[0][2] = 4;
	mest2[0][3] = -4;
	mest2[1][0] = 3;
	mest2[1][1] = -2;
	mest2[1][2] = 0;
	mest2[1][3] = 1;
	mest2[2][0] = 2;
	mest2[2][1] = 5;
	mest2[2][2] = 6;
	mest2[2][3] = 7;
	cout << mest2 << endl;
	cout << m_mult (mest1, mest2) << endl;
	cout << mest1.minor (0, 1) << endl;
	cout << m_det (mest1) << endl;
	cout << m_inv (mest1) << endl;
}
