/* Simple linked list with integer attribute
Method covered:
Initialization, Addition, Deletion, Deletion of entire node
*/

#include <stdio.h>
#include <stdlib.h>
#define true 1
static int size = 0;

struct ListNode{
	int n;
	struct ListNode *next;
};
typedef struct ListNode ListNode;

void allocate(ListNode* head)
{
	head->next = (ListNode*)malloc(sizeof(ListNode));
}

void print(ListNode* head)
{
	while(head != NULL)
	{
		printf("%d\n",head->n);
		head = head->next;
	}
}
//head is pointer to pointer so as to check the case in which addition is
//in starting(we wouldn't need to return pointer in that case)
void InsertInLinkedList(ListNode** head, int d, int position)
{
	int k = 1;
	ListNode *newNode,*p,*q;
	p = *head;//p also points to starting of the linked list
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->n = d;
	if(position > size)
	{
		printf("Error Out of Index");
		return;
	}
	if(position == 1)//adding at the start of the list
	{
		newNode->next = *head;
		*head = newNode;
	}
	else//in starting the p points to starting and k = 1
	{
		while((p != NULL)&& k < position)//stop when p points to position where addition has to be done
		{
			k++;
			q = p;
			p = p->next;
		}
		//in the end p points to the node at position, pos.
		//q points to the previous node, at position, pos. - 1 
		q->next = newNode;//remember that q->next paradigm that we discussed
		newNode->next = p;
		size++;
	}
}

void DeleteNodeLinkedList(ListNode **head,int pos)
{
	int k = 1;
	ListNode *p,*q;
	p = *head;//p points to starting of list
	if(pos > size)
	{
		printf("Not possible to delete");
		return;
	}
	if(pos == 1)
	{
		*head = p->next;
		//equivalently *head = (*head)->next;
		free(p);
		return;
	}
	while(k < pos)
	{
		k++;
		q = p;
		p = p->next;
	}
	//in the end p points to the node which has to be removed
	//q points to the node previous to the one which has to be removed
	q->next = p->next;
	free(p);//we have explicitly free the memory pointed by the pointer
}

void delete(ListNode** head)
{
	ListNode *q,*p;
	p = *head;
	while(p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	*head = NULL;
}

int main()
{
	int d,i;
	ListNode *head,*start;
	head = (ListNode*)malloc(sizeof(ListNode));
	start = head;//must do this after allocation
	scanf("%d",&d);
	while(true)
	{
		head->n = d;
		size++;
		scanf("%d",&d);
		if(d == -1) break;
		allocate(head);
		head = head->next;
	}
	head->next = NULL;//we can't be sure about the garbage value assigned by default
	printf("Orignal linked list\n");
	print(start);//even after this call start still points to starting of list
	printf("Inserting in the linked list, data & position\n");
	scanf("%d %d",&d,&i);//i = 1 means starting of linkd list
	InsertInLinkedList(&start,d,i);
	print(start);
	printf("Deletion from the linked list, position\n");
	scanf("%d",&i);//deletion from position i
	DeleteNodeLinkedList(&start,i);
	print(start);
	printf("Deleting the entire linked list\n");
	delete(&start);
}
