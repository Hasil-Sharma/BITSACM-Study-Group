#include <stdio.h>
#include "BSTDef.h"

BST* createEmptyBST();
BST* insert_BST(BST*, Book*);
void inOrderVisit(book_node*);
boolean find_BST(BST*,Book*);
BST* delete_BST(BST*,Book*);