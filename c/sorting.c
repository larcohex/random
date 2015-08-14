#include <stdlib.h>


void bubbleSort (int *arr, int size)
{
	int i, j, temp;
	for (i = 0; i < size - 1; ++i)
	{
		for (j = 0; j < size - 1 - i; ++j)
		{
			if (arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}




void selectionSort (int *arr, int size)
{
	int i, j, min = -1, temp1, temp2;
	for (i = 0; i < size - 1; ++i)
	{
		for (j = i; j < size; ++j)
		{
			if (min == -1 || arr[j] < min)
			{
				min = arr[j];
				temp1 = j;
			}
		}
		temp2 = arr[i];
		arr[i] = min;
		arr[temp1] = temp2;
		min = -1;
	}
}


void quickSort (int *arr, int size)
{
	int *less, *greater, *equal;
	int i, j, mean, lsize = 0, esize = 0, gsize = 0;
	if (size)
	{
		less = (int *) malloc (sizeof (int) * size);
		equal = (int *) malloc (sizeof (int) * size);
		greater = (int *) malloc (sizeof (int) * size);
		mean = ((arr[0] + arr[size-1]) / 2) % size;
		for (i = 0; i < size; ++i)
		{
			if (arr[i] < arr[mean])
			{
				less[lsize] = arr[i];
				++lsize;
			}
			else if (arr[i] == arr[mean])
			{
				equal[esize] = arr[i];
				++esize;
			}
			else
			{
				greater[gsize] = arr[i];
				++gsize;
			}
		}
		quickSort (less, lsize);
		quickSort (greater, gsize);
		for (i = 0; i < lsize; ++i)
		{
			arr[i] = less[i];
		}
		for (j = 0; j < esize; ++i, ++j)
		{
			arr[i] = equal[j];
		}
		for (j = 0; j < gsize; ++i, ++j)
		{
			arr[i] = greater[j];
		}
		free (less);
		free (equal);
		free (greater);
	}
}
