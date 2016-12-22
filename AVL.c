//
// Created by igor on 24/10/15.
//

#include "AVL.h"

//TODO: Make this code more generic

node* makeNode(unsigned int id, long key){
    node *p = (node*) malloc(sizeof(node));
    p->ID = id;
    p->key = key;
    p->leftSon = NULL;
    p->rightSon = NULL;
    p->balance = 0;
    return p;
}

void rightRotation(node **Tree){

    node *aux = (*Tree)->leftSon;

    (*Tree)->leftSon = aux->rightSon;
    aux->rightSon = *Tree;
    *Tree = aux;
}

void leftRotation(node **Tree){

    node *aux  = (*Tree)->rightSon;

    (*Tree)->rightSon = aux->leftSon;
    aux->leftSon = *Tree;
    *Tree = aux;
}

void balanceFix(node *Tree, int dependency) {

    Tree->balance = 0;

    /* Fix balance based on given information */
    switch (dependency){
        case -1:
            Tree->leftSon->balance  = 0;
            Tree->rightSon->balance = 1;
            break;
        case  0:
            Tree->leftSon->balance  = 0;
            Tree->rightSon->balance = 0;
            break;
        case  1:
            Tree->leftSon->balance  =-1;
            Tree->rightSon->balance = 0;
            break;
    }
}

void treatLeftInsertion(node** Tree, char* flag){

    (*Tree)->balance--;

    if((*Tree)->balance == 0)
        *flag = 0;

    else if((*Tree)->balance == -2)
    {
        if((*Tree)->leftSon->balance == -1)
        {
            rightRotation(Tree);
            (*Tree)->balance = 0;
            (*Tree)->rightSon->balance = 0;
        }
        else
        {
            int balance = (*Tree)->leftSon->rightSon->balance;
            leftRotation(&(*Tree)->leftSon);
            rightRotation(Tree);
            balanceFix(*Tree, balance);
        }
        *flag = 0;
    }
}

void treatRightInsertion(node** Tree, char* flag){

    (*Tree)->balance++;

    if((*Tree)->balance == 0)
        *flag = 0;

    else if((*Tree)->balance == 2)
    {
        if((*Tree)->rightSon->balance == 1)
        {
            leftRotation(Tree);
            (*Tree)->balance = 0;
            (*Tree)->leftSon->balance = 0;
        }
        else
        {
            int balance = (*Tree)->rightSon->leftSon->balance;
            rightRotation(&(*Tree)->rightSon);
            leftRotation(Tree);
            balanceFix(*Tree, balance);
        }
        *flag = 0;
    }
}

void insertNode(node** Tree, unsigned int id, long key, char* flag){
    {
        if(*Tree == NULL){
            *Tree = makeNode(id, key);
            *flag = 1;
        } else {
            if((*Tree)->ID > id)
            {
                insertNode(&((*Tree)->leftSon), id, key, flag);
                if(*flag == 1)
                    treatLeftInsertion(&(*Tree), flag);
            }
            else
            {
                insertNode(&((*Tree)->rightSon), id, key, flag);
                if(*flag == 1)
                    treatRightInsertion(&(*Tree), flag);
            }
        }
    }
}

void treatLeftReduction(node** Tree, char* flag){

    (*Tree)->balance++;

    if((*Tree)->balance == 1)
        *flag = 0;

    else if ((*Tree)->balance == 2)
    {
        short shortCut = (*Tree)->rightSon->balance;

        switch (shortCut){
            case 1:
                leftRotation(Tree);
                (*Tree)->balance = 0;
                (*Tree)->leftSon->balance = 0;
                *flag = 1;
                break;
            case 0:
                leftRotation(Tree);
                (*Tree)->balance = -1;
                (*Tree)->leftSon->balance = 1;
                *flag = 0;
                break;
            case -1:
                shortCut = (*Tree)->rightSon->leftSon->balance;
                rightRotation(&(*Tree)->rightSon);
                leftRotation(Tree);
                balanceFix(*Tree, shortCut);
                *flag = 1;
                break;
        }
    }
}

void treatRightReduction(node** Tree, char* flag){
    (*Tree)->balance--;

    if((*Tree)->balance == -1)
        *flag = 0;

    else if ((*Tree)->balance == -2)
    {
        short shortCut = (*Tree)->leftSon->balance;

        switch (shortCut){
            case -1:
                rightRotation(Tree);
                (*Tree)->balance = 0;
                (*Tree)->rightSon->balance = 0;
                *flag = 1;
                break;
            case 0:
                rightRotation(Tree);
                (*Tree)->balance = 1;
                (*Tree)->rightSon->balance = -1;
                *flag = 0;
                break;
            case 1:
                shortCut = (*Tree)->leftSon->rightSon->balance;
                leftRotation(&(*Tree)->leftSon);
                rightRotation(Tree);
                balanceFix(*Tree, shortCut);
                *flag  = 1;
                break;
        }
    }
}

void removeNode(node** Tree, char* flag, unsigned int id){
    if((*Tree) != NULL)
    {
        if ((*Tree)->ID == id)
        {
            if ((*Tree)->rightSon != NULL && (*Tree)->leftSon != NULL)
            {
                node *p = (*Tree)->rightSon, copia = *(*Tree);

                while (p->leftSon != NULL)
                    p = p->leftSon;

                (*Tree)->ID    = p->ID;
                (*Tree)->key = p->key;
                p->ID = copia.ID;
                p->key = copia.key;

                removeNode(&(*Tree)->rightSon, flag, id);

            }else{

                if ((*Tree)->leftSon != NULL)
                {
                    node *p = (*Tree)->leftSon;
                    *(*Tree) = *(*Tree)->leftSon;
                    free(p);
                }
                else if((*Tree)->rightSon != NULL)
                {
                    node *p = (*Tree)->rightSon;
                    *(*Tree) = *(*Tree)->rightSon;
                    free(p);
                }else
                {
                    free((*Tree));
                    *Tree = NULL;
                }
                *flag = 1;
            }
        } else if ((*Tree)->ID > id) {
            removeNode(&((*Tree)->leftSon), flag, id);
            if(*flag == 1)
                treatLeftReduction(&(*Tree), flag);
        }
        else
        {
            removeNode(&((*Tree)->rightSon), flag, id);
            if(*flag == 1)
                treatRightReduction(&(*Tree), flag);
        }
    }
}

void destroyTree(node** No){
    node *p=*No;

    if (p != NULL){
        destroyTree(&(p->rightSon));
        destroyTree(&(p->leftSon));
        free(p);
        *No = NULL;
    }
}

int altura(node* T){
    if (T != NULL)
        return 1 + MAX(altura(T->leftSon), altura(T->rightSon));
    else
        return(0);
}

void printTree(node* T, int h, int altura){
    int i;

    if (T != NULL)
    {
        printTree(T->rightSon, h + 1, altura);

        for (i = 0; i < h; i++)
            printf("        ");

        printf("%u(%hd)", T->ID, T->balance);

        for (i = 0; i < altura-h; i++)
            printf("--------");

        printf("\n");

        printTree(T->leftSon, h + 1, altura);
    }
}