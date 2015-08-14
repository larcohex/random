#ifndef LAB4_H
#define LAB4_H
#include <stdio.h>
#include <stdlib.h>

#define DATA(p) ((p)->data)
#define NEXT(p) ((p)->next)
#define PREV(p) ((p)->prev)

int *a;
int n;

int getNext();



typedef struct node
{
	int data;
	struct node *prev;
	struct node *next;
} node;

node *ex1, *ex2;


void print_list (node *head);
node *create_list();
int sum (node *head);
void delete_node (node **head, int value);
void insert_node (node **head, int value);
node *combine (node *first, node *second);
void execute();
#endif
