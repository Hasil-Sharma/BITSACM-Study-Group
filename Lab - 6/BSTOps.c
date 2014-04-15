#include <stdio.h>
#include <stdlib.h>
#include "BSTOps.h"

BST* createEmptyBST()
{
	BST* newTree = NULL;
	while(!newTree)
		newTree = (BST*)malloc(sizeof(BST));
	newTree->root = NULL;
	newTree->totalBooks = 0;
	newTree->height = 0;
	return newTree;
}
book_node* insert_node(book_node* bk, Book *b)
{
	if(bk == NULL)
	{
		while(!bk)
			bk = (book_node*)malloc(sizeof(book_node));
		bk->book = b;
		bk->left = bk->right = NULL;
	}
	else
	{
		if(bk->book->accNum > b->accNum)
			bk->left = insert_node(bk->left,b);
		else bk->right = insert_node(bk->right,b);
	}
	return bk;
}

BST* insert_BST(BST* bt, Book* b)
{
	//bt is BST, totalBooks, heigth , root//pointer
	bt->root = insert_node(bt->root,b);
	bt->totalBooks++;
	return bt;
}

void visit(Book* b)
{
	printf("%d %d\n",b->accNum,b->price);
}

void inOrderVisit(book_node* root)
{
	if(root)
	{
		inOrderVisit(root->left);
		visit(root->book);
		inOrderVisit(root->right);
	}
}

boolean find_node(book_node* root,int data)
{
	if(!root) return False;
	if(root->book->accNum == data)
		return True;
	else
	{
		if(root->book->accNum > data)
			return find_node(root->left,data);
		else return find_node(root->right,data);
	}
}

boolean find_BST(BST* bt, Book* b)
{
	return find_node(bt->root,b->accNum);
}

book_node* findMax(book_node* root)
{
	if(root == NULL) return root;
	else
	{
		if(root->right == NULL) return root;
		else return findMax(root->right);
	}
}

book_node* delete_node(book_node* root, Book* b)
{
	book_node* temp = NULL;
	if(root->book->accNum > b->accNum)
		root->left = delete_node(root->left,b);
	else if(root->book->accNum < b->accNum)
		root->right = delete_node(root->right,b);
	else
	{
		//node is found !!!
		if(root->left && root->right)
		{
			temp = findMax(root->left);
			root->book = temp->book;
			root->left = delete_node(root->left,temp->book);
		}
		else
		{
			temp = root;
			if(root->left == NULL)
				root = root->right;
			else if(root->right == NULL)
				root = root->left;
			free(temp);
		}
	}
	return root;
}
BST* delete_BST(BST* bt, Book* b)
{
	bt->root = delete_node(bt->root,b);
	bt->totalBooks--;
	return bt;
}