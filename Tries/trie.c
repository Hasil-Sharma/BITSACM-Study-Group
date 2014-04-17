//based on http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=usingTries

#include <stdio.h>

typedef struct trie_node
{
	int words;			//used only for last \0 key
	int prefixes;
	struct trie_node *children[26];
}trie_node;

trie_node* get_new_node()
{
	trie_node *ptr;
	ptr = (trie_node *)malloc(sizeof(trie_node));
	if (ptr)
	{
		ptr->words = 0;
		ptr->prefixes = 0;
		int i;
		for (i = 0; i < 26; i++)
		{			
			ptr->children[i] = NULL;
		}
	}
	return ptr;
}

void insert (trie_node* root, char *str)
{
	//printf("\nNow inserting %c\n", str[0]);
	if (str[0] == '\0')
	{
		root->words++;
	}
	else
	{
		root->prefixes++;
		int key = (int)str[0] - (int)'a';
		if (root->children[key] == NULL)
		{
			root->children[key] = get_new_node();
		}
		str = str + 1;				//cut the first character and recursively call insert
		insert (root->children[key], str);
	}
}

int count_words (trie_node* root, char *str)
{
	//printf("\nSearching for %s\n", str);
	int key = (int)str[0] - (int)'a';
	if (str[0] == '\0')
	{
		return root->words;
	}
	else if (root->children[key] == NULL)
	{
		return 0;
	}
	else
	{
		//printf("Going into children of %c\n", (char) (key+97));
		return count_words (root->children[key], str + 1);			//cut leftmost character and go further in
	}
}


int count_prefixes (trie_node* root, char *str)
{
	int key = (int)str[0] - (int)'a';
	if (str[0] == '\0')
	{
		return root->prefixes;
	}
	else if (root->children[key] == NULL)
	{
		return 0;
	}
	else
	{
		return count_prefixes (root->children[key], str + 1);
	}
}

int main()
{
	trie_node *ptr;
	ptr = get_new_node();
	int choice=0, result;
	char str[40];
	
	while (choice != 5)
	{
		printf("\n\nWELCOME\n");
		printf("1. Insert a word\n");
		printf("2. Search for a word\n");
		printf("3. Count number of words beginning with a string\n");
		printf("4. Exit\n\n");
		
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				printf ("Enter word to insert\n");
				scanf ("%s", &str);
				insert (ptr, str);
				break;
				
			case 2:
				printf ("Enter word to search for\n");
				scanf ("%s", &str);
				result = count_words (ptr, &str);
				if (result)
				{
					printf ("Word EXISTS!\n");
				}
				else
				{					
					printf ("Word does NOT exist!\n");
				}
				break;
				
			case 3:
				printf("Enter starting of string\n");
				scanf("%s", &str);
				result = count_prefixes (ptr, &str);
				printf("Number of strings starting with %s : %d\n", str, result);
				break;
			
			case 4:
				choice = 5;
				break;
				
			default:
				printf("Idiot\n");
		}
	}
	return 0;
}
