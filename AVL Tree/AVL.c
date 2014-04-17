#include <stdio.h>
#include <stdlib.h>

struct AVLTreeNode{
	struct AVLTreeNode *left;
	int data;
	struct AVLTreeNode *right;
	int height;
};

int Height(struct AVLTreeNode *root)
{
	if(!root) return -1;
	else return root->height;
}

int max(int a, int b)
{
	return ( a > b ) ? a : b;
}
struct AVLTreeNode *SingleRotateLeft(struct AVLTreeNode* x)
{
	struct AVLTreeNode *y = x->right;
	struct AVLTreeNode *T2 = y->left;

	x->right = T2;
	y->left = x;

	y->height = max(Height(y->left), Height(y->right))+1;
    x->height = max(Height(x->left), Height(x->right))+1;

	return y;

}

struct AVLTreeNode *SingleRotateRight(struct AVLTreeNode* y)
{
	struct AVLTreeNode *x = y->left;
    struct AVLTreeNode *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(Height(y->left), Height(y->right))+1;
    x->height = max(Height(x->left), Height(x->right))+1;
 
    // Return new root
    return x;
}

struct AVLTreeNode *Insert(struct AVLTreeNode* root, int data)
{
	if(!root)
	{
		root = (struct AVLTreeNode*)malloc(sizeof(struct AVLTreeNode));
		if(!root)
			root = (struct AVLTreeNode*)malloc(sizeof(struct AVLTreeNode));
		root->data = data;
		root->height = 0;
		root->left = root->right = NULL;
	}
	else if(data < root->data)
	{
		root->left = Insert(root->left,data);
		if((Height(root->left) - Height(root->right)) > 1)
		{
			//node(root) is unbalanced
			//either Left Left or Left Right
			if(data > root->left->data)
			{
				//must be in Left Right
				root->left = SingleRotateLeft(root->left);
				root = SingleRotateRight(root);
			}
			else
			{
				//must be in Left Left
				root = SingleRotateRight(root);
			}
		}
		
	}
	else if(data > root->data)
	{
		root->right = Insert(root->right,data);
		if(Height(root->left) - Height(root->right) < -1)
		{
			//node(root) is unbalanced
			//either Right Left or Right Right
			if(data > root->right->data)
			{
				//must be in Right Right
				root = SingleRotateLeft(root);
			}
			else
			{
				//must be Right Left
				root->right = SingleRotateRight(root->right);
				root = SingleRotateLeft(root);
			}

		}
	}
	root->height = max(Height(root->left),Height(root->right)) + 1;
	return root;
}

void visit(struct AVLTreeNode* root)
{
	if(root)
	{
		visit(root->left);
		printf("%d\n",root->data);
		visit(root->right);
	}
}

int main()
{
	struct AVLTreeNode* root = NULL;
	int i,d;
	for(i = 0; i < 10; i++)
	{
		d = rand()%1000;
		printf("Inserting :%d\n",d);
		root = Insert(root,d);
	}
	visit(root);
	printf("Height of tree %d\n",Height(root));
	return 0;
}