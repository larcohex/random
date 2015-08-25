#include <iostream>
#include <vector>
#include <string>

using namespace std;


class SortClass
{
	private:


		void merge (vector <int> &v, int begin, int end)
		{
			int middle = (begin + end) / 2;
			vector <int> sorted;
			int i, j;
			for (i = begin, j = middle + 1; i <= middle && j <= end;)
			{
				if (v[i] < v[j])
				{
					sorted.push_back (v[i]);
					++i;
				}
				else
				{
					sorted.push_back (v[j]);
					++j;
				}
			}
			while (i <= middle)
			{
				sorted.push_back (v[i]);
				++i;
			}
			while (j <= end)
			{
				sorted.push_back (v[j]);
				++j;
			}
			for (i = begin; i <= end; ++i)
			{
				v[i] = sorted [i-begin];
			}
		}

		void mergeSortHelper (vector <int> &v, int begin, int end)
		{
			if (end > begin)
			{
				int middle = (begin + end) / 2;
				mergeSortHelper (v, begin, middle);
				mergeSortHelper (v, middle + 1, end);
				merge (v, begin, end);
			}
		}



	public:

		void bubbleSort (vector <int> &v)
		{
			for (int i = 0; i < v.size() - 1; ++i)
			{
				for (int j = 0; j < v.size() - i - 1; ++j)
				{
					if (v[j] > v[j + 1])
					{
						int temp = v[j];
						v[j] = v[j + 1];
						v[j + 1] = temp;
					}
				}
			}
		}


		void insertionSort (vector <int> &v)
		{
			for (int i = 1; i < v.size(); ++i)
			{
				for (int j = i; j > 0 && v[j] < v[j - 1]; --j)
				{
					int temp = v[j];
					v[j] = v[j - 1];
					v[j - 1] = temp;
				}
			}
		}


		void selectionSort (vector <int> &v)
		{
			for (int i = 0; i < v.size() - 1; ++i)
			{
				int min = 0;
				int pos = -1;
				for (int j = i + 1; j < v.size(); ++j)
				{
					if (!min || v[j] < min)
					{
						min = v[j];
						pos = j;
					}
				}
				if (min && min < v[i])
				{
					v[pos] = v[i];
					v[i] = min;
				}
			}
		}


		void mergeSort (vector <int> &v)
		{
			mergeSortHelper (v, 0, v.size() - 1);
		}

		void radixSort (vector <int> &v)
		{
			for (int i = 0; i < 32; ++i)
			{
				unsigned int radix = (1 << i);
				int temp[v.size()];
				int temp0 = 0;
				int temp1 = 0;
				for (int j = 0; j < v.size(); ++j)
				{
					if (!(v[j] & radix))
						++temp1;
				}
				for (int j = 0; j < v.size(); ++j)
				{
					if (v[j] & radix)
					{
						temp[temp1] = v[j];
						++temp1;
					}
					else
					{
						temp[temp0] = v[j];
						++temp0;
					}
				}
				for (int j = 0; j < v.size(); ++j)
				{
					v[j] = temp[j];
				}
			}
		}
};


int main()
{
	vector <int> test;
	test.push_back (2);
	test.push_back (5);
	test.push_back (1);
	test.push_back (4);
	test.push_back (3);
	SortClass testClass;
	testClass.radixSort (test);
	for (int i = 0; i < test.size(); ++i)
	{
		cout << test[i] << endl;
	}
}
