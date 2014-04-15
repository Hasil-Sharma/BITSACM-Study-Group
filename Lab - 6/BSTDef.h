#include <stdio.h>
enum boolean
{
	True = 1,
	False = 0
};

typedef enum boolean boolean;

struct _BST{
	int totalBooks;
	int height;
	struct book_node* root;
};

typedef struct _BST BST;

struct book{
	int accNum;
	int price;
	char* auth;
	char* title;//point
};

typedef struct book Book;
typedef struct book_node book_node;
struct book_node{
	Book* book;
	book_node* left;
	book_node* right;
};


