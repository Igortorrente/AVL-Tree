//
// Created by igor on 24/10/15.
//

#ifndef LAB06_AVL_H
#define LAB06_AVL_H

#include <stdlib.h>
#include <stdio.h>

#define MAX(x, y) ((x > y) ? x : y)

//TODO: Colocar essa arvore dentro de uma struct
//Node of tree
typedef struct no{
    //TODO: remove ID and key. Insert void pointer
    unsigned int ID;
    long int key;
    short int balance;
    struct no *leftSon, *rightSon;
}node;

//TODO: Improve printTree

void insertNode(node** Tree, unsigned int id, long key, char* flag);
void removeNode(node** Tree, char* flag, unsigned int id);
void destroyTree(node** No);
int  altura(node* T);
void printTree(node* T, int h, int altura);

#endif //LAB06_AVL_H
