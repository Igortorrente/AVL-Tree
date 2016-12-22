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
        short int var = (*Tree)->rightSon->balance;

        if(var == 0 || var == 1)
        {
            node *p = (*Tree)->rightSon,*q = p->leftSon;
            p->leftSon = (*Tree);
            (*Tree)->rightSon = q;
            (*Tree) = p;

            if(var == 0)
            {
                *flag = 0;
                p->leftSon->balance = 1;
                p->balance = -1;
            }
            else
            {
                p->leftSon->balance = 0;
                p->balance = 0;
            }
        }
        else if(var == -1)
        {
            node *p = (*Tree)->rightSon->leftSon, *q = p->leftSon, *r = p->rightSon;
            p->leftSon = (*Tree);
            p->rightSon = (*Tree)->rightSon;
            (*Tree)->rightSon = q;
            p->rightSon->leftSon = r;

            if(p->balance == -1)
            {
                (*Tree)->balance = 0;
                p->rightSon->balance = 1;
            }
            else if(p->balance  == 1)
            {
                (*Tree)->balance = -1;
                p->rightSon->balance = 0;
            }
            else
            {
                (*Tree)->balance = 0;
                p->rightSon->balance = 0;
            }
            (*Tree) = p;
            p->balance = 0;
        }
    }
}

void treatRightReduction(node** Tree, char* flag){
    (*Tree)->balance--;
    if((*Tree)->balance == -1)
        *flag = 0;
    else if ((*Tree)->balance == -2)
    {
        short int var = (*Tree)->leftSon->balance;
        if(var == 0 || var == -1)
        {
            node *p = (*Tree)->leftSon,*q = p->rightSon;
            p->rightSon = (*Tree);
            (*Tree)->leftSon = q;
            switch(p->balance)
            {
                case 0:
                    (*Tree)->balance = -1;
                    p->balance = +1;
                    *flag = 0;
                    break;
                case -1:
                    (*Tree)->balance = 0;
                    p->balance = 0;
                    break;
                default:
                    break;
            }
            (*Tree) = p;
        }
        else if(var == 1)
        {
            node *p = (*Tree)->leftSon->rightSon, *q = p->leftSon,*r = p->rightSon;
            p->rightSon = (*Tree);
            p->leftSon = (*Tree)->leftSon;
            p->leftSon->rightSon = q;
            (*Tree)->leftSon = r;
            switch(p->balance)
            {
                case -1:
                    (*Tree)->balance = 0;
                    p->leftSon->balance = 1;
                    break;
                case 1:
                    (*Tree)->balance = -1;
                    p->leftSon->balance =  0;
                    break;
                case 0:
                    (*Tree)->balance =  0;
                    p->leftSon->balance =  0;
                    break;
                default:
                    break;
            }
            (*Tree) = p;
            p->balance = 0;
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