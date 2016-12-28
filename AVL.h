#ifndef LAB06_AVL_H
#define LAB06_AVL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX(x, y) ((x > y) ? x : y)

typedef int (*CompPointer)(const void*, const void*);

//TODO:Implement number of nodes, numerical error returns;

//Node of tree
typedef struct no{
    void* ID;
    char balance;
    struct no* leftSon, *rightSon;
}node;

//Struct with base of tree and pointer to function comparator
typedef struct avl{
    node* avlTree;
    CompPointer comparator;
}AVL;

void avlInitializer(AVL* Tree);
void ClearTree(node** No);
bool empty(AVL Tree);
void* getnode(AVL Tree, void* id);
void insertNode(AVL* Tree, void* id);
void removeNode(AVL* Tree, void* id);
bool searchNode(AVL Tree, void* id);
void setComparator(AVL* Tree, CompPointer userComparator);
int  altura(node* T);
void printTree(node* T, int h, int altura);


/*User comparator prototype :
 * int YourComparator(yourdata A, yourdata B)
 * Expected returns :  1 if  A > B
 *                     0 if  A == B
 *                    -1 if  A < B        */

#endif //LAB06_AVL_H
