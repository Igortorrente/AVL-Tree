#include "AVL.h"

node* makeNode(void* id) {
    node *p = (node*) malloc(sizeof(node));
    p->ID = malloc(sizeof(id));
    memcpy(p->ID, id, sizeof(id));
    p->leftSon = NULL;
    p->rightSon = NULL;
    p->balance = 0;
    return p;
}

void avlInitializer(AVL* Tree){
    Tree->avlTree = NULL;
    Tree->comparator = NULL;
}

void setComparator(AVL* Tree, CompPointer userComparator){
    Tree->comparator = userComparator;
}

void rightRotation(node** dad){

    node *aux = (*dad)->leftSon;

    (*dad)->leftSon = aux->rightSon;
    aux->rightSon = *dad;
    *dad = aux;
}

void leftRotation(node** dad){

    node *aux  = (*dad)->rightSon;

    (*dad)->rightSon = aux->leftSon;
    aux->leftSon = *dad;
    *dad = aux;
}

void balanceFix(node* dad, int dependency) {

    dad->balance = 0;

    /* Fix balance based on given information */
    switch (dependency){
        case -1:
            dad->leftSon->balance  = 0;
            dad->rightSon->balance = 1;
            break;
        case  0:
            dad->leftSon->balance  = 0;
            dad->rightSon->balance = 0;
            break;
        case  1:
            dad->leftSon->balance  =-1;
            dad->rightSon->balance = 0;
            break;
    }
}

void treatLeftInsertion(node** dad, char* flag){

    (*dad)->balance--;

    switch((*dad)->balance){
        case 0:
            *flag = 0;
            break;
        case -2:
            if((*dad)->leftSon->balance == -1){
                rightRotation(dad);
                (*dad)->balance = 0;
                (*dad)->rightSon->balance = 0;
            } else {
                int balance = (*dad)->leftSon->rightSon->balance;
                leftRotation(&(*dad)->leftSon);
                rightRotation(dad);
                balanceFix(*dad, balance);
            }
            *flag = 0;
            break;
    }
}

void treatRightInsertion(node** dad, char* flag){

    (*dad)->balance++;

    switch((*dad)->balance){
        case 0:
            *flag = 0;
            break;
        case 2:
            if((*dad)->rightSon->balance == 1){
                leftRotation(dad);
                (*dad)->balance = 0;
                (*dad)->leftSon->balance = 0;
            } else {
                int balance = (*dad)->rightSon->leftSon->balance;
                rightRotation(&(*dad)->rightSon);
                leftRotation(dad);
                balanceFix(*dad, balance);
            }
            *flag = 0;
            break;
    }
}

void treatLeftReduction(node** dad, char* flag){

    (*dad)->balance++;

    //TODO:rename This variable
    short shortCut;
    switch((*dad)->balance){
        case 1:
            *flag = 0;
            break;
        case 2:
            shortCut = (*dad)->rightSon->balance;
            switch (shortCut){
                case 1:
                    leftRotation(dad);
                    (*dad)->balance = 0;
                    (*dad)->leftSon->balance = 0;
                    *flag = 1;
                    break;
                case 0:
                    leftRotation(dad);
                    (*dad)->balance = -1;
                    (*dad)->leftSon->balance = 1;
                    *flag = 0;
                    break;
                case -1:
                    shortCut = (*dad)->rightSon->leftSon->balance;
                    rightRotation(&(*dad)->rightSon);
                    leftRotation(dad);
                    balanceFix(*dad, shortCut);
                    *flag = 1;
                    break;
            }
            break;
    }
}

void treatRightReduction(node** dad, char* flag){

    (*dad)->balance--;

    short shortCut;
    switch((*dad)->balance){
        case -1:
            *flag = 0;
            break;
        case -2:
            shortCut = (*dad)->leftSon->balance;
            switch (shortCut){
                case -1:
                    rightRotation(dad);
                    (*dad)->balance = 0;
                    (*dad)->rightSon->balance = 0;
                    *flag = 1;
                    break;
                case 0:
                    rightRotation(dad);
                    (*dad)->balance = 1;
                    (*dad)->rightSon->balance = -1;
                    *flag = 0;
                    break;
                case 1:
                    shortCut = (*dad)->leftSon->rightSon->balance;
                    leftRotation(&(*dad)->leftSon);
                    rightRotation(dad);
                    balanceFix(*dad, shortCut);
                    *flag  = 1;
                    break;
            }
            break;
    }
}

//TODO: Tratar caso em que o retorno do comparador está fora das especificações
void insertNodeR(node** dad, CompPointer userComparator, void* id, char* flag) {

    if(*dad == NULL){
        *dad = makeNode(id);
        *flag = 1;
    } else {
        if(userComparator((*dad)->ID, id) == 1){
            insertNodeR(&(*dad)->leftSon, userComparator, id, flag);
            if(*flag == 1)
                treatLeftInsertion(&(*dad), flag);
        } else {
            insertNodeR(&(*dad)->rightSon, userComparator, id, flag);
            if(*flag == 1)
                treatRightInsertion(&(*dad), flag);
        }
    }
}

void removeNodeR(node** dad, CompPointer userComparator, void* id, char* flag) {

    if(*dad != NULL){

        if (userComparator((*dad)->ID, id) == 0){

            if ((*dad)->rightSon != NULL && (*dad)->leftSon != NULL) {

                node *p = (*dad)->rightSon, copy = *(*dad);

                while (p->leftSon != NULL)
                    p = p->leftSon;

                (*dad)->ID = p->ID;
                p->ID = copy.ID;
                removeNodeR(&(*dad)->rightSon, userComparator, id, flag);

            }else{

                if ((*dad)->leftSon != NULL){

                    node* p = (*dad)->leftSon;
                    *(*dad) = *(*dad)->leftSon;
                    free(p);

                } else if((*dad)->rightSon != NULL) {

                    node* p = (*dad)->rightSon;
                    *(*dad) = *(*dad)->rightSon;
                    free(p);

                } else {
                    free((*dad)->ID);
                    free(*dad);
                    *dad = NULL;
                }
                *flag = 1;
            }

        } else if (userComparator((*dad)->ID, id) == 1) {

            removeNodeR(&(*dad)->leftSon, userComparator, id, flag);
            if(*flag == 1)
                treatLeftReduction(&(*dad), flag);

        } else {

            removeNodeR(&(*dad)->rightSon, userComparator, id, flag);
            if(*flag == 1)
                treatRightReduction(&(*dad), flag);

        }
    }
}

void insertNode(AVL* Tree, void* id){
    char flag = 0;
    insertNodeR(&(Tree->avlTree), Tree->comparator, id, &flag);
}

void removeNode(AVL* Tree, void* id){
    char flag = 0;
    removeNodeR(&Tree->avlTree, Tree->comparator, id, &flag);
}

bool searchNode(AVL* Tree, void* id){
    
    node* nextNode = Tree->avlTree;

    while(nextNode != NULL){
        switch(Tree->comparator(nextNode->ID, id)){
            case 0:
                return true;
            case 1:
                nextNode = nextNode->leftSon;
                break;
            case -1:
                nextNode = nextNode->rightSon;
                break;
        }
    }
    return false;
}

bool empty(AVL* Tree) {
    if(Tree->avlTree != NULL)
        return false;
    return true;
}

void* getnode(AVL* Tree, void* id){
    node* nextNode = Tree->avlTree;

    while(nextNode != NULL){
        switch(Tree->comparator(nextNode->ID, id)){
            case 0:
                return nextNode->ID;
            case 1:
                nextNode = nextNode->leftSon;
                break;
            case -1:
                nextNode = nextNode->rightSon;
                break;
            default:
                printf("A função comparadora está fora das especificações\n");
                return NULL;
        }
    }
    return NULL;
}

void destroyTree(node** No){

    node* p = *No;

    if (p != NULL){
        destroyTree(&(p->rightSon));
        destroyTree(&(p->leftSon));
        free(p->ID);
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

//Vai dar crash com qualquer outro dado
void printTree(node* T, int h, int altura){
    int i;

    if (T != NULL){

        printTree(T->rightSon, h + 1, altura);

        for (i = 0; i < h; i++)
            printf("        ");

        printf("%d(%hd)", *((int*)T->ID), T->balance);

        for (i = 0; i < altura-h; i++)
            printf("--------");

        printf("\n");

        printTree(T->leftSon, h + 1, altura);
    }
}
