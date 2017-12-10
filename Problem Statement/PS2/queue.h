#include <stdlib.h>

using namespace std;
using namespace cv;

typedef struct _node
{
	int i,j;
	struct _node* next;
}node;

typedef struct _queue
{
	node* last;
	node* head;
}queue;

void init(queue* a)
{
	a->head=NULL;
	a->last=a->head;
}

int isEmpty(queue* a)
{
	if(a->head==NULL)
	{
		return 1;
	}

	else 
		return 0;
}

void enqueue(queue* a, int i, int j)
{
	node* ex=(node*)malloc(sizeof(node));

	ex->i=i;
	ex->j=j;

	if(a->head==NULL)
		a->head=a->last=ex;

	else
	{
		(a->last)->next=ex;
		a->last=ex;
	}
}

void dequeue(queue* a)
{

	if(a->head==NULL) return;

	else if(a->head==a->last)
	{
		a->head=NULL;
		a->last=a->head;
	}

	else
	{
		a->head=(a->head)->next;
	}
}
