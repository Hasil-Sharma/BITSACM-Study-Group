#include <stdio.h>
#include <stdlib.h>
typedef struct linkedlist linkedlist;
linkedlist* insert(linkedlist*,int);

struct linkedlist
{
	int data;
	linkedlist* next;
};

int main()
{
	int d;
	linkedlist* root = NULL;
	for(d = 0; d < 10; d++)
	{
		printf("inserting %d\n",d);
		root = insert(root,d);
	}
	insert(root,-1);
	while(root->data != -1)
	{
		printf("%d\n",root->data);
		root= root->next;
	}
}

linkedlist* insert(linkedlist* root, int d)
{
	if(root == NULL)
	{
		root = (linkedlist*)malloc(sizeof(linkedlist));
		root->data = d;
		root->next = NULL;
	}
	else root->next = insert(root->next,d);
	return root;
}