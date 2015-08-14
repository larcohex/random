#include <string.h>
#include <stdlib.h>
#define TAG(vp)   ((vp)->tag)
#define LABEL(vp) ((vp)->label)  
#define EDGE(vp)  ((vp)->edge)

typedef struct vertex 
{
	char tag;
	char *label;
	struct vertex *edge[1];
}
vertex, *vp;


typedef struct adjList
{
	vp node;
	struct adjList *next;
}
adjList;


adjList *createList (vp graph)
{
	int i;
	adjList *result, *ptr, *ptr2;
	if (graph)
	{
		result = malloc (sizeof (adjList));
		result->node = graph;
		ptr2 = result;
		for (i = 0; EDGE (graph)[i]; ++i)
		{
			ptr = malloc (sizeof (adjList));
			ptr->node = EDGE (graph)[i];
			ptr2->next = ptr;
			ptr2 = ptr;
		}
		ptr2->next = NULL;
	}
	return result;
}


void createListsHelper (adjList ***result, vp graph, int *index)
{
	int i;
	if (graph)
	{
		(*result) = realloc ((*result), sizeof (adjList *) * ((*index) + 2));
		(*result)[(*index)] = createList (graph);
		TAG (((*result)[(*index)])->node) = 'a';
		for (i = 0; EDGE (graph)[i]; ++i)
		{
			if (TAG (EDGE (graph)[i]) != 'a')
			{
				++(*index);
				createListsHelper (result, EDGE (graph)[i], index);
			}
		}
	}
}


adjList **createLists (vp graph)
{
	adjList **result = malloc (sizeof (adjList *));
	int *index = malloc (sizeof (int));
	*index = 0;
	createListsHelper (&result, graph, index);
	result[*index + 1] = NULL;
	free (index);
	return result;
}



adjList *copyList (adjList *list)
{
	adjList *ptr, *ptr2, *ptr3;
	adjList *result = malloc (sizeof (adjList));
	result->node = list->node;
	ptr2 = result;
	for (ptr = list; ptr->next; ptr = ptr->next)
	{
		ptr3 = malloc (sizeof (adjList));
		ptr3->node = ptr->next->node;
		ptr2->next = ptr3;
		ptr2 = ptr3;
	}
	ptr2->next = NULL;
	return result;
}


void destroy (adjList *list)
{
	if (list)
	{
		destroy (list->next);
		free (list);
	}
}


void destroyLists (adjList **lists)
{
	int i;
	for (i = 0; lists[i]; ++i)
	{
		destroy (lists[i]);
	}
	free (lists);
}

void insert (vp node, adjList *list)
{
	adjList *ptr;
	for (ptr = list; ptr->next; ptr = ptr->next)
	{
	}
	ptr->next = malloc (sizeof (adjList));
	ptr->next->node = node;
	ptr->next->next = NULL;
}


int find (vp node, adjList *list)
{
	int result = 0;
	adjList *ptr;
	for (ptr = list; ptr; ptr = ptr->next)
	{
		if (!strcmp (LABEL (node), LABEL (ptr->node)))
		{
			result = 1;
			return result;
		}
	}
	return result;
}

adjList *mergeList (adjList *list1, adjList *list2)
{
	adjList *ptr;
	adjList *result = copyList (list1);
	for (ptr = list2; ptr; ptr = ptr->next)
	{
		if (!find (ptr->node, list1))
		{
			insert (ptr->node, result);
		}
	}
	return result;
}


adjList **mergeLists (adjList **list1, adjList **list2)
{
	int found;
	int i, j;
	int size = 0;
	adjList **result;
	adjList *temp;
	for (i = 0; list1[i]; ++i)
	{
		++size;
	}
	result = malloc (sizeof (adjList *) * size);
	for (i = 0; list1[i]; ++i)
	{
		result[i] = copyList (list1[i]);
	}
	for (i = 0; list2[i]; ++i)
	{
		found = 0;
		for (j = 0; j < size; ++j)
		{
			if (!strcmp (LABEL (list2[i]->node), LABEL (result[j]->node)))
			{
				temp = mergeList (result[j], list2[i]);
				destroy (result[j]);
				result[j] = temp;
				found = 1;
			}
		}
		if (!found)
		{
			++size;
			result = realloc (result, sizeof (adjList *) * size);
			result[size-1] = copyList (list2[i]);
		}
	}
	++size;
	result = realloc (result, sizeof (adjList *) * size);
	result[size - 1] = NULL;
	return result;
}


int countNeighbours (adjList *list)
{
	adjList *ptr;
	int result = 0;
	for (ptr = list->next; ptr; ptr = ptr->next)
	{
		++result;
	}
	return result;
}


vp merge (vp graph1, vp graph2)
{
	int i, j, k, temp;
	int *nn, n = 0;
	vp *nodes, tempvp;
	adjList *ptr, **gr1, **gr2, **totalList;
	gr1 = createLists (graph1);
	gr2 = createLists (graph2);
	totalList = mergeLists (gr1, gr2);
	destroyLists (gr1);
	destroyLists (gr2);
	for (i = 0; totalList[i]; ++i)
	{
		++n;
	}
	nn = malloc (sizeof (int) * n);
	for (i = 0; i < n; ++i)
	{
		nn[i] = countNeighbours (totalList[i]);
	}
	nodes = malloc (sizeof (vp) * n);
	for (i = 0; i < n; ++i)
	{
		nodes[i] = malloc (sizeof (vertex) + (nn[i] * sizeof (vp)));
		LABEL (nodes[i]) = malloc (sizeof (char) * (strlen (LABEL (totalList[i]->node)) + 1));
		strcpy (LABEL (nodes[i]), LABEL (totalList[i]->node));
	}
	for (i = 0; i < n; ++i)
	{
		temp = 0;
		for (ptr = totalList[i]->next; ptr; ptr = ptr->next)
		{
			for (j = 0; strcmp (LABEL (ptr->node), LABEL (nodes[j])); ++j)
			{
			}
			EDGE (nodes[i])[temp] = nodes[j];
			++temp;
		}
	}
	destroyLists (totalList);
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < nn[i] - 1; ++j)
		{
			for (k = 0; k < nn[i] - 1 - j; ++k)
			{
				if (strcmp (LABEL (EDGE (nodes[i])[k]), LABEL (EDGE (nodes[i])[k + 1])) > 0)
				{
					tempvp = EDGE (nodes[i])[k];
					EDGE (nodes[i])[k] = EDGE (nodes[i])[k + 1];
					EDGE (nodes[i])[k + 1] = tempvp;
				}
			}
		}
	}
	free (nn);
	return nodes[0];
}
