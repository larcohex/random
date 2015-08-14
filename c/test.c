#include "lab4.h"

int getNext()
{
	++n;
	return a[n - 1];
}


int main()
{
	n = 0;
	ex1 = malloc (sizeof (node));
	PREV (ex1) = NULL;
	DATA (ex1) = 2;
	NEXT (ex1) = malloc (sizeof (node));
	PREV (NEXT (ex1)) = ex1;
	DATA (NEXT (ex1)) = 5;
	NEXT (NEXT (ex1)) = malloc (sizeof (node));
	PREV (NEXT (NEXT (ex1))) = NEXT (ex1);
	DATA (NEXT (NEXT (ex1))) = 7;
	NEXT (NEXT (NEXT (ex1))) = malloc (sizeof (node));
	PREV (NEXT (NEXT (NEXT (ex1)))) = NEXT (NEXT (ex1));
	DATA (NEXT (NEXT (NEXT (ex1)))) = 9;
	NEXT (NEXT (NEXT (NEXT (ex1)))) = NULL;
	ex2 = malloc (sizeof (node));
	PREV (ex2) = NULL;
	DATA (ex2) = 20;
	NEXT (ex2) = malloc (sizeof (node));
	PREV (NEXT (ex2)) = ex1;
	DATA (NEXT (ex2)) = 50;
	NEXT (NEXT (ex2)) = malloc (sizeof (node));
	PREV (NEXT (NEXT (ex2))) = NEXT (ex1);
	DATA (NEXT (NEXT (ex2))) = 70;
	NEXT (NEXT (NEXT (ex2))) = malloc (sizeof (node));
	PREV (NEXT (NEXT (NEXT (ex2)))) = NEXT (NEXT (ex1));
	DATA (NEXT (NEXT (NEXT (ex2)))) = 90;
	NEXT (NEXT (NEXT (NEXT (ex2)))) = NULL;
	a = malloc (sizeof (int) * 5);
	a[0] = 7;
	a[1] = 3;
	a[2] = 5;
	a[3] = 4;
	a[4] = -1;
	execute();
	return 0;
}
