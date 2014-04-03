#include <stdio.h>
#include <stdlib.h>

typedef struct linkedlist linkedlist;
typedef struct coordinates coordinates;
struct coordinates
{
	int x;
	int y;
};

struct linkedlist{
	coordinates data;
	linkedlist *next;
};

void allocate(linkedlist* ptr)//method
{
	ptr->next = (linkedlist*)malloc(sizeof(linkedlist));//pointer points to some memory location
}

void display(linkedlist* ptr)
{
	do
	{
		printf("%d %d\n",ptr->data.x,ptr->data.y);
		ptr = ptr->next;
	}while(ptr->data.x != -1);
}

int main()
{
	int x,y;
	linkedlist *head,*start;//initiall head was NULL
	scanf("%d %d",&x,&y);
	head = (linkedlist*)malloc(sizeof(linkedlist));
	start = head;
	head->data.x = x;
	head->data.y = y;
	do
	{
		scanf("%d %d",&x,&y);
		allocate(head);
		head->next->data.x = x;
		head->next->data.y = y;
		head = head->next;
	}while(x != -1);

	display(start);
	return 0;
}