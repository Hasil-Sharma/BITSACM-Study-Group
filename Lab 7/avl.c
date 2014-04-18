#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* You can see the difference, using AVL tree: 17 height,
using Binary Tree: height is 32*/

typedef struct linkedlist linkedlist;
typedef struct avltreenode avltreenode;

char* sanitize(char*);
avltreenode* insert(avltreenode*,char*,int);
linkedlist* insertInLL(linkedlist*,int);
int compare(char*,char*);
void inOrder(avltreenode*);
void visit(avltreenode*);
int height(avltreenode*);
int max(int,int);
avltreenode* rightrotate(avltreenode*);
avltreenode* lefrotate(avltreenode*);
void populateSucc(avltreenode*);
struct linkedlist{
	int value;
	linkedlist* next;
};


struct avltreenode{
	char *word;
	linkedlist *head;
	avltreenode *left,*right,*succ;
	int height;
};


int main()
{
	avltreenode* root = NULL;
	char word[1000],*stword;
	int wordnum = 0;
	//really don't know if I should do this setting 
	//1000 char limit
	FILE *fptr;
	fptr = fopen("new.txt","r");
	while(fscanf(fptr,"%s",word) != EOF)
	{
		stword = sanitize(word);
		//printf("Inserting word: %s\n",stword);
		root = insert(root,stword,wordnum++);
		//for finding word position we can use fseek
		//but this logic is much more intuitive
	}
	fclose(fptr);
	populateSucc(root);
	inOrder(root);
	printf("Height of tree: %d\n",root->height);
	return 0;
}

char *sanitize(char *word)
{
	int len = strlen(word),i,j;
	char *nword = (char*)malloc(len*sizeof(char));
	for(i = 0,j = 0; i < len; i++)
	{
		if((word[i] >= 65 && word[i] <= 90) || (word[i] >= 97 && word[i] <= 122))
		{
			nword[j++] = word[i];
		}
	}
	//nword[j] = '\0';
	return nword;
}

avltreenode* insert(avltreenode* root, char* word, int pos)
{
	if(root == NULL)
	{
		root = (avltreenode*)malloc(sizeof(avltreenode));
		root->left = root->right = root->succ = NULL;
		root->head = NULL;
		//must set root->head == NULL before insertion
		//why ? Think over :P
		root->head = insertInLL(root->head,pos);
		root->word = word;
		root->height = 0;
	}
	else
	{
		//root is not NULL must find the correct position
		if(compare(root->word,word) > 0)
		{
			//root->word > word; hence left subtree
			root->left = insert(root->left,word,pos);
			if((height(root->left) - height(root->right)) > 2)
			{
				//root node is imbalanced
				if(compare(root->word,word) > 0)
				{
					//left left case
					root = rightrotate(root);
				}
				else
				{
					//left right case
					root->left = lefrotate(root->left);
					root = rightrotate(root);
				}
			}
		}
		else if(compare(root->word,word) < 0)
		{
			//right subtree
			root->right = insert(root->right,word,pos);
			if((height(root->left) - height(root->right)) < -2)
			{
				//root node is imbalanced
				if(compare(root->word,word) > 0)
				{
					//right left case
					root->right = rightrotate(root->right);
					root = rightrotate(root);
				}
				else
				{
					//right right case
					root = lefrotate(root);
				}
			}
		}
		else
		{
			//word matches
			//simply add the position to it's linked list;
			root->head = insertInLL(root->head,pos);
		}
	}
	root->height = max(height(root->left),height(root->right))+1;
	return root;
}

//recursively adding to linkedlist
//this is advanced might take a minute, ANALYZE
linkedlist* insertInLL(linkedlist* root, int pos)
{
	if(root == NULL)
	{
		root = (linkedlist*)malloc(sizeof(linkedlist));
		root->value = pos;
		root->next = NULL;
	}
	else root->next = insertInLL(root->next,pos);
	return root;
}
int compare(char* a, char* b)
{
	return strcmp(a,b);
}
void inOrder(avltreenode* root)
{
	while(root)
	{
		visit(root);
		root = root->succ;
	}
}

void visit(avltreenode* root)
{
	linkedlist* head;
	head = root->head;
	printf("%s:",root->word);
	while(head)
	{
		printf(" %d",head->value);
		head = head->next;
	}
	printf("\n");
}

int height(avltreenode* root)
{
	if(!root) return -1;
	return root->height;
}

int max(int a,int b)
{
	return (a > b) ? a : b;
}

avltreenode* rightrotate(avltreenode* root)
{
	avltreenode* x = root->left;
	avltreenode* temp = x->right;

	//rotation
	x->right = root;
	root->left = temp;

	//update the height
	root->height = max(height(root->left), height(root->right))+1;
	x->height = max(height(root->left),height(root->right))+1;

	return x;
}

avltreenode* lefrotate(avltreenode* root)
{
	avltreenode* x = root->right;
	avltreenode* temp = x->left;

	//rotation
	root->right = temp;
	x->left = root;

	root->height = max(height(root->left), height(root->right))+1;
	x->height = max(height(root->left),height(root->right))+1;

	return x;
}

void populateSucc(avltreenode* root)
{
	static avltreenode* next = NULL;
	if(root)
	{
		populateSucc(root->right);
		root->succ = next;
		next = root;
		populateSucc(root->left);
	}
}