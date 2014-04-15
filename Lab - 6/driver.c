#include <stdio.h>
#include <stdlib.h>
#include "BSTOps.h"

int main()
{
	Book* b;
	BST* newTree = NULL;
	newTree = createEmptyBST();
	while(True)
	{
		b = (Book*)malloc(sizeof(Book));
		scanf("%d %d",&b->accNum, &b->price);
		if(b->accNum == -1) break;
		newTree = insert_BST(newTree,b);
	}
	inOrderVisit(newTree->root);
	b->accNum = 10;
	b->price = 589;
	(find_BST(newTree,b) == True) ? printf("Yo\n") : printf("No\n");
	newTree = delete_BST(newTree,b);
	inOrderVisit(newTree->root);
	return 0;
}