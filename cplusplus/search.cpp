#include <iostream>
#include <vector>

using namespace std;


int seqSearch (vector <int> &a, int toFind)
{
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] == toFind)
			return i;
	}
	return -1;
}


int biSearch (vector <int> &a, int toFind)
{
	int max = a.size() - 1;
	int min = 0;
	while (min <= max)
	{
		int mid = (max - min) / 2;
		cout << max << " " << min << endl;
		if (a[mid] == toFind)
			return mid;
		else if (a[mid] < toFind)
			max = mid - 1;
		else
			min = mid + 1;
	}
	return -1;
}



int intSearch (vector <int> &a, int toFind)
{
	int max = a.size() - 1;
	int min = 0;
	while (min <= max)
	{
		int mid = min + ( (toFind - a[min]) * (max - min) ) / (a[min] - a[max]);
		cout << mid << endl;
		if (a[mid] == toFind)
			return mid;
		else if (a[mid] < toFind)
			max = mid - 1;
		else
			min = mid + 1;
	}
	return -1;
}

int main()
{
	vector <int> a;
	for (int i = 0; i < 100; ++i)
	{
		a.push_back (i);
	}
	seqSearch (a, 23);
	biSearch (a, 23);
	intSearch (a, 23);
}
