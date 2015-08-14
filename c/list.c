#include <stdio.h>
#include <stdlib.h>
#include "lab4.h"


void print_list (node *head)
{
	if (head)
	{
		printf ("%d ", DATA (head));
		print_list (NEXT (head));
	}
}



	
node *create_list()
{
	int temp;
	node *ptr1, *ptr2;
	node *result = malloc (sizeof (node));
	PREV (result) = NULL;
	DATA (result) = getNext();
	ptr2 = result;
	while (1)
	{
		temp = getNext();
		if (temp == -1)
			break;
		else
		{
			ptr1 = malloc (sizeof (node));
			DATA (ptr1) = temp;
			PREV (ptr1) = ptr2;
			NEXT (ptr2) = ptr1;
			ptr2 = ptr1;
		}
	}
	NEXT (ptr2) = NULL;
	return result;
}



int sum (node *head)
{
	if (head)
		return DATA (head) + sum (NEXT (head));
	else
		return 0;
}



void delete_node (node **head, int value)
{
	node *toDelete, *pr, *nxt;
	if (head)
	{
		if (*head)
		{
			if (DATA (*head) == value)
			{
				toDelete = *head;
				pr = PREV (*head);
				nxt = NEXT (*head);
				NEXT (pr) = nxt;
				PREV (nxt) = pr;
				free (toDelete);
			}
			else
				delete_node (&(NEXT (*head)), value);
		}
	}			
}



void insert_node (node **head, int value)
{
	node *ptr;
	node *newNode = malloc (sizeof (node));
	DATA (newNode) = value;
	if (value < DATA (*head))
	{
		PREV (newNode) = NULL;
		NEXT (newNode) = *head;
		PREV (*head) = newNode;
		*head = newNode;
	}
	else
	{
		for (ptr = *head; NEXT (ptr); ptr = NEXT (ptr))
		{
			if (value < DATA (NEXT (ptr)))
			{
				PREV (newNode) = ptr;
				NEXT (newNode) = NEXT (ptr);
				NEXT (ptr) = newNode;
				PREV (NEXT (newNode)) = newNode;
				break;
			}
		}
		if (!NEXT (ptr))
		{
			PREV (newNode) = ptr;
			NEXT (newNode) = NULL;
			NEXT (ptr) = newNode;
		}
	}
}


	
node *combine (node *first, node *second)
{
	node *temp1, *temp2;
	node *ptr1, *ptr2;
	temp1 = temp2 = NULL;
	for (ptr1 = first, ptr2 = second; ptr1 && ptr2; ptr1 = temp1, ptr2 = temp2)
	{
		temp1 = NEXT (ptr1);
		temp2 = NEXT (ptr2);
		NEXT (ptr1) = ptr2;
		PREV (ptr2) = ptr1;
		NEXT (ptr2) = temp1;
		if (temp1)
			PREV (temp1) = ptr2;
		if (temp2)
			PREV (temp2) = NULL;
	}
	return first;
}

void execute()
{
	node *result, *result2;
	print_list (ex1);
	printf ("\n");
	result = create_list();
	print_list (result);
	printf ("\n");
	printf ("Sum is %d\n", sum (ex1));
	delete_node (&ex1, 7);
	printf ("After\n");
	print_list (ex1);
	printf ("\n");
	insert_node (&ex1, 10);
	printf("After\n");
	print_list (ex1);
	printf ("\n");
/*	result2 = combine (ex1, ex2);
	printf("result: ");
	print_list(result2);
	printf ("\n"); */
}
