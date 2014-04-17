#include <stdio.h>
#include <stdlib.h>
struct AVLTreeNode
{
	int data;
	int height;
	struct AVLTreeNode *right,*left;
};

typedef struct AVLTreeNode AVLTreeNode;

int height(AVLTreeNode* root)
{
	if(root == NULL) return -1;
	else
		return root->height;
}
int max(int a, int b)
{
	return (a>b) ? a : b;
}
AVLTreeNode* rightrotation(AVLTreeNode* root)
{
	AVLTreeNode* x = root->left;
	AVLTreeNode* temp = x->right;

	x->right = root;
	root->left = temp;

	x->height = max(height(x->left),height(x->right)) + 1;
	root->height = max(height(root->left),height(root->right)) + 1;

	return x;
}

AVLTreeNode* leftrotation(AVLTreeNode* root)
{
	AVLTreeNode* x = root->right;
	AVLTreeNode* temp = x->left;

	root->right = temp;
	x->left = root;

	x->height = max(height(x->left),height(x->right)) + 1;
	root->height = max(height(root->left),height(root->right)) + 1;

	return x;
}
AVLTreeNode* insert(AVLTreeNode* root,int data)
{
	if(root == NULL)
	{
		root = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
		root->data = data;
		root->left = root->right = NULL;
		root->height = 0;
	}
	else
	{
		if(data > root->data)
		{
			root->right = insert(root->right,data);
			if((height(root->left) - height(root->right)) < -1)
			{
				//root node is imbalanced
				if(data > root->right->data)
				{
					//node is right right
					//single left rotation
					root = leftrotation(root);
				}
				else
				{
					//node is right left
					//right rotation with left rotation
					root->right = rightrotation(root->right);
					root = leftrotation(root);
				}
			}
		}
		else
		{
			root->left = insert(root->left,data);
			if((height(root->left) - height(root->right)) > 1)
			{
				//root node is imbalanced
				if(data > root->left->data)
				{
					//node is left right
					//left rotation with right rotation
					root->left = leftrotation(root->left);
					root = rightrotation(root);
				}
				else
				{
					//node is left left
					//single right rotation
					root = rightrotation(root);
				}
			}
		}
	}
	root->height = max(height(root->left),height(root->right))+1;
	return root;
}

void visit(AVLTreeNode* root)
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
	AVLTreeNode* root = NULL;
	int i,d;
	for(i = 1; i <= 25; i++)
	{
		d = rand()%1000;
		root = insert(root,d);
	}
	visit(root);

	printf("height : %d\n",height(root));
	return 0;
}