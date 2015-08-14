#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#include <ctime>
#include <cstdlib>

using namespace std;


int pow (int base, int exp)
{
	int result = 1;
	for (int i = 0; i < exp; ++i)
	{
		result *= base;
	}
	return result;
}


float calcTime (float speed)
{
	return 100 / speed;
}


vector <int> quickSort (vector <int> &a)
{
	int size = a.size();
	if (size == 1 || !size)
		return a;

	int median;
	vector <int> less;
	vector <int> equal;
	vector <int> greater;
	if (a[0] < a[size - 1])
	{
		if (a[0] >= a[size/2])
			median = 0;
		else
		{
			if (a[size/2] < a[size - 1])
				median = size / 2;

			else
				median = size - 1;
		}
	}
	else
	{
		if (a[0] < a[size/2])
			median = 0;
		else
		{
			if (a[size/2] >= a[size - 1])
				median = size / 2;

			else
				median = size - 1;
		}
	}
	for (int i = 0; i < size; ++i)
	{
		if (a[i] < a[median])
			less.push_back (a[i]);
		else if (a[i] == a[median])
			equal.push_back (a[i]);
		else
			greater.push_back (a[i]);
	}
	less = quickSort (less);
	greater = quickSort (greater);
	less.insert (less.end(), equal.begin(), equal.end());
	less.insert (less.end(), greater.begin(), greater.end());
	return less;
}


void shellSort (vector <int> &a)
{
	int k = 0;
	while (pow (2, k) - 1 < a.size())
		++k;
	--k;
	while (k > 0)
	{
		int gap = pow (2, k) - 1;
		int pos = 0;
		while (pos < a.size())
		{
			for (int i = pos; i > 0 && a[i] < a[i-gap]; i -= gap)
			{
				int temp = a[i];
				a[i] = a[i-gap];
				a[i-gap] = temp;
			}
			pos += gap;
		}
		--k;
	}
}


void insertionSort (vector <int> &a)
{
	for (int i = 0; i < a.size(); ++i)
	{
		for (int j = i; j > 0 && a[j] < a[j-1]; --j)
		{
			int temp = a[j];
			a[j] = a[j-1];
			a[j-1] = temp;
		}
	}
}


vector <int> bucketSort (vector <int> &a)
{
	int max = 0;
	float range;
	vector <vector <int> > buckets;
	vector <int> result;
	for (int i = 0; i < 10; ++i)
	{
		vector <int> temp;
		buckets.push_back (temp);
	}
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] > max)
			max = a[i];
	}
	range = max / 10;
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] >= 0 && a[i] < range)
			buckets[0].push_back (a[i]);
		else if (a[i] >= range && a[i] < range * 2)
			buckets[1].push_back (a[i]);
		else if (a[i] >= range * 2 && a[i] < range * 3)
			buckets[2].push_back (a[i]);
		else if (a[i] >= range * 3 && a[i] < range * 4)
			buckets[3].push_back (a[i]);
		else if (a[i] >= range * 4 && a[i] < range * 5)
			buckets[4].push_back (a[i]);
		else if (a[i] >= range * 5 && a[i] < range * 6)
			buckets[5].push_back (a[i]);
		else if (a[i] >= range * 6 && a[i] < range * 7)
			buckets[6].push_back (a[i]);
		else if (a[i] >= range * 7 && a[i] < range * 8)
			buckets[7].push_back (a[i]);
		else if (a[i] >= range * 8 && a[i] < range * 9)
			buckets[8].push_back (a[i]);
		else if (a[i] >= range * 9 && a[i] <= max)
			buckets[9].push_back (a[i]);
	}
	for (int i = 0; i < 10; ++i)
	{
		insertionSort (buckets[i]);
	}
	for (int i = 0; i < 10; ++i)
	{
		result.insert (result.end(), buckets[i].begin(), buckets[i].end());
	}
	return result;
}


void radixSort (vector <int> &a)
{
	for (int i = 0; i < 32; ++i)
	{
		unsigned int radix = (1 << i);
		int temp[a.size()];
		int temp0 = 0;
		int temp1 = 0;
		for (int j = 0; j < a.size(); ++j)
		{
			if (!(a[j] & radix))
				++temp1;
		}
		for (int j = 0; j < a.size(); ++j)
		{
			if (a[j] & radix)
			{
				temp[temp1] = a[j];
				++temp1;
			}
			else
			{
				temp[temp0] = a[j];
				++temp0;
			}
		}
		for (int j = 0; j < a.size(); ++j)
		{
			a[j] = temp[j];
		}
	}
}


int main()
{
	ofstream output;
	output.open ("sort.out");
	srand (unsigned (time (0)));
	vector <int> test;
	for (int i = 1; i <= 50; ++i)
	{
		test.push_back (i);
	}
	random_shuffle (test.begin(), test.end());


	vector <int> temp;

	output << "Array of 50 elements" << endl;
	output << "Quick sort: ";
	temp = test;
	struct timeval tv_begin;
	struct timeval tv_end;
	int passed_milliseconds;
	gettimeofday (&tv_begin, NULL);
	temp = quickSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Shell sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	shellSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Bucket sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	temp = bucketSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Radix sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	radixSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;




	output << "\n" << endl;
	test.clear();
	for (int i = 1; i <= 100; ++i)
	{
		test.push_back (i);
	}
	random_shuffle (test.begin(), test.end());
	output << "Array of 100 elements" << endl;
	output << "Quick sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	temp = quickSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Shell sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	shellSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Bucket sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	temp = bucketSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Radix sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	radixSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;





	output << "\n" << endl;
	test.clear();
	for (int i = 1; i <= 500; ++i)
	{
		test.push_back (i);
	}
	random_shuffle (test.begin(), test.end());
	output << "Array of 500 elements" << endl;
	output << "Quick sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	temp = quickSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Shell sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	shellSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Bucket sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	temp = bucketSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Radix sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	radixSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;





	output << "\n" << endl;
	test.clear();
	for (int i = 1; i <= 1000; ++i)
	{
		test.push_back (i);
	}
	random_shuffle (test.begin(), test.end());
	output << "Array of 1000 elements" << endl;
	output << "Quick sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	temp = quickSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Shell sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	shellSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Bucket sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	temp = bucketSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Radix sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	radixSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;





	output << "\n" << endl;
	test.clear();
	for (int i = 1; i <= 5000; ++i)
	{
		test.push_back (i);
	}
	random_shuffle (test.begin(), test.end());
	output << "Array of 5000 elements" << endl;
	output << "Quick sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	temp = quickSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Shell sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	shellSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Bucket sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	temp = bucketSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Radix sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	radixSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;





	output << "\n" << endl;
	test.clear();
	for (int i = 1; i <= 10000; ++i)
	{
		test.push_back (i);
	}
	random_shuffle (test.begin(), test.end());
	output << "Array of 10000 elements" << endl;
	output << "Quick sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	temp = quickSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Shell sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	shellSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Bucket sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	temp = bucketSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;

	output << "Radix sort: ";
	temp = test;
	gettimeofday (&tv_begin, NULL);
	radixSort (temp);
	gettimeofday (&tv_end, NULL);
	passed_milliseconds = (tv_end.tv_sec - tv_begin.tv_sec) * 1000 + (tv_end.tv_usec -
tv_begin.tv_usec) / 1000;
	output << passed_milliseconds << endl;
	for (int i = 0; i < temp.size(); ++i)
	{
		output << temp[i] << " ";
	}
	output << endl;
}
