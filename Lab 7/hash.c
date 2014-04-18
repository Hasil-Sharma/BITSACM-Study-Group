#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define mod 511

typedef struct linkedList linkedList;
typedef struct chainNode chainNode;
typedef struct hashTable hashTable;

hashTable* createNewTable();
char* sanitize(char*);
int hash(char*);
void insert(hashTable*,char*,int,int);
linkedList* insertInLL(linkedList*,int);
chainNode* findInChainNode(chainNode*,char*);
chainNode* insertNewChainNode(chainNode*,char*,int);
void printTable(chainNode**);

struct linkedList
{
	int pos;
	linkedList* next;
};

struct chainNode
{
	linkedList* head;
	char* word;
	chainNode* nextChainNode;
};

struct hashTable
{
	chainNode** start;//pointer to an array of pointers essentially
	//alternatively we can make another structure, but why not to use the power pointers give
};


int main()
{
	char word[1000],*stword;
	int wordnum = 0,hashNum;
	FILE *fptr;
	hashTable* table = NULL;
	table = createNewTable();
	fptr = fopen("new.txt","r");
	while(fscanf(fptr,"%s",word) != EOF)
	{
		stword = sanitize(word);
		//printf("Inserting word: %s\n",stword);
		hashNum = hash(stword);
		insert(table,stword,hashNum,wordnum++);
		//printf("%s :%d\n",stword,hashNum);
		//for finding word position we can use fseek
		//but this logic is much more intuitive
	}
	printTable(table->start);
}

hashTable* createNewTable()
{
	int i;
	hashTable* newTable;
	newTable = (hashTable*)malloc(sizeof(hashTable));
	newTable->start = (chainNode**)malloc(mod*sizeof(chainNode*));
	//not
	//newTable->start = (chainNode*)malloc(mod*sizeof(chainNode))
	//we want an array of pointers not an array of structures
	for(i = 0; i < mod; i++)
		newTable->start[i] = NULL;
	//initializing the hashtable to NULL
	return newTable;
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
	//nword[j] = '\0';
	return nword;
}

int hash(char *word)
{
	int i, sum = 0, len = strlen(word);
	for(i = 0; i < len; i++)
	{
		sum += word[i];
	}
	return sum%mod;
}

void insert(hashTable* table,char* word, int hashNum, int pos)
{
	chainNode* chainStart = table->start[hashNum];
	if(table->start[hashNum] == NULL)
	{
		table->start[hashNum] = (chainNode*)malloc(sizeof(chainNode));
		chainNode* chainStart = table->start[hashNum];
		chainStart->head = NULL;
		chainStart->nextChainNode = NULL;
		chainStart->word = word;
		chainStart->head = insertInLL(chainStart->head,pos);
	}
	else
	{
		chainNode *temp = findInChainNode(chainStart,word);
		//finding if the current word is already in the 
		//chain nodes
		if(temp == NULL)
		{
			//addition to the end of the list
			//make a new chainNode and everything
			table->start[hashNum] = insertNewChainNode(chainStart,word,pos);
		}
		else
		{
			//add the value of pos to the linked list
			//in the chainNode
			temp->head = insertInLL(temp->head,pos);
		}
	}

}

linkedList* insertInLL(linkedList* root, int pos)
{
	if(root == NULL)
	{
		root = (linkedList*)malloc(sizeof(linkedList));
		root->pos = pos;
		root->next = NULL;
	}
	else root->next = insertInLL(root->next,pos);
	return root;
}

chainNode* findInChainNode(chainNode* start,char* word)
{
	if(!start) return NULL;
	if(strcmp(start->word,word) == 0) return start;
	else return findInChainNode(start->nextChainNode,word);
}

chainNode* insertNewChainNode(chainNode* start,char* word,int pos)
{
	if(start == NULL)
	{
		start = (chainNode*)malloc(sizeof(chainNode));
		start->head = NULL;
		start->head = insertInLL(start->head,pos);
		start->word = word;
		start->nextChainNode = NULL;
	}
	else start->nextChainNode = insertNewChainNode(start->nextChainNode,word,pos);
	return start;
}

void printTable(chainNode** start)
{
	int i;
	chainNode* temp;
	linkedList* head;
	for(i = 0; i < mod; i++)
	{
		temp = start[i];
		printf("For the words hashed to %d:\n",i);
		while(temp)
		{
			printf("%s:",temp->word);
			head = temp->head;
			while(head)
			{
				printf(" %d",head->pos);
				head = head->next;
			}
			temp = temp->nextChainNode;
			printf("\n");
		}
		printf("\n");
	}
	printf("\n");
}