#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trie_node trie_node;

trie_node* createNewtrie();
char* sanitize(char*);
trie_node* insert(trie_node*,char*);
void print(trie_node*);

struct trie_node
{
	int boolean;
	trie_node* children[26];
};

int main()
{
	char word[1000],*stword;
	int wordnum = 0,hashNum;
	trie_node* root = NULL;
	FILE *fptr;
	fptr = fopen("new.txt","r");
	while(fscanf(fptr,"%s",word) != EOF)
	{
		stword = sanitize(word);
		//printf("Inserting word: %s\n",stword);
		root = insert(root,stword);
		//printf("%s :%d\n",stword,hashNum);
	}
	return 0;
}
trie_node* createNewtrie()
{
	int i;
	trie_node* root;
	root = (trie_node*)malloc(sizeof(trie_node));
	root->boolean = 0;
	for(i = 0; i < 26; i++)
		root->children[i] = NULL;
	print(root);
	return root;
}
char *sanitize(char *word)
{
	int len = strlen(word),i,j;
	char *nword = (char*)malloc(len*sizeof(char));
	for(i = 0,j = 0; i < len; i++)
	{
		if((word[i] >= 65 && word[i] <= 90) || (word[i] >= 97 && word[i] <= 122))
		{
			if(word[i] >= 'A' && word[i] <= 'Z')
				word[i] += 32;
			nword[j++] = word[i];
		}
	}
	nword[j] = '\0';
	return nword;
}

trie_node* insert(trie_node* root,char* word)
{
	int index;
	index = word[0] - 'a';
	printf("inserting: %c\n",word[0]);
	if(word[0] == '\0')
	{
		//making it a leaf node
		if(root == NULL)
		{
			root = createNewtrie();
			root->boolean = 1;
		}
	}
	else if(root == NULL && word[0] != '\0')
	{
		//character is not present
		root = createNewtrie();
		root->boolean = 0;
		root->children[index] = insert(root->children[index],++word);
	}
	else
	{
		//that character is already present
		root->children[index] = insert(root->children[index],++word);
		root->boolean = 0;
		//might have been a leaf node
	}

	return root;
}