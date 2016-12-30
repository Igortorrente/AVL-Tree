#include "AVL.h"


//USER FUNCTIONS

//Initialize struct AVL
void avlInitializer(AVL* Tree){
    Tree->avlTree = NULL;
    Tree->comparator = NULL;
}

/*Remove all nodes of tree
 *Parameters : 1 - address node pointer. (&(ExampleTree.avlTree))
 *Return     : void  */
void ClearTree(node** No){

    node* p = *No;

    if (p != NULL){
        ClearTree(&(p->rightSon));
        ClearTree(&(p->leftSon));
        free(p->ID);
        free(p);
        *No = NULL;
    }
}

/*Verify if Tree is empty
 *Parameters : 1 - Struct AVL
 *Return     : Bool - False if tree is empty / True else  */
bool empty(AVL Tree) {
    if(Tree.avlTree != NULL)
        return false;
    return true;
}

/*Return content of required node
 *Parameters : 1 - Struct AVL, 2 - Node you want get the content
 *Return     : void* return a pointer to node content  */
void* getnode(AVL Tree, void* id){
    node* nextNode = Tree.avlTree;

    while(nextNode != NULL){
        switch(Tree.comparator(nextNode->ID, id)){
            case 0:
                return nextNode->ID;
            case 1:
                nextNode = nextNode->leftSon;
                break;
            case -1:
                nextNode = nextNode->rightSon;
                break;
            default:
                return NULL;
        }
    }
    return NULL;
}

/*User function insert node
 *Parameters : 1 - Struct AVl , 2 - Data you want put in tree
 *Return     : Void  */
void insertNode(AVL* Tree, void* id){
    char flag = 0;
    insertNodeR(&(Tree->avlTree), Tree->comparator, id, &flag);
}

/*User function remove node
 *Parameters : 1 - Struct AVl , 2 - Data you want remove in tree
 *Return     : void  */
void removeNode(AVL* Tree, void* id){
    char flag = 0;
    removeNodeR(&Tree->avlTree, Tree->comparator, id, &flag);
}

/*Return if node are in tree
 *Parameters : 1 - Struct AVl , 2 - Data you want search in tree
 *Return     : bool - False if node if not in tree / True else  */
bool searchNode(AVL Tree, void* id){

    node* nextNode = Tree.avlTree;

    while(nextNode != NULL){
        switch(Tree.comparator(nextNode->ID, id)){
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

//Copy the address of function comparator to struct AVL
void setComparator(AVL* Tree, CompPointer userComparator){
    Tree->comparator = userComparator;
}

//TODO: Remove this function...
int altura(node* T){
    if (T != NULL)
        return 1 + MAX(altura(T->leftSon), altura(T->rightSon));
    else
        return(0);
}

//And This
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


//PRIVATE FUNCTIONS


//Create a node and initialize their content
node* makeNode(void* id){
    node *p = (node*) malloc(sizeof(node));
    p->ID = malloc(sizeof(id));
    memcpy(p->ID, id, sizeof(id));
    p->leftSon = NULL;
    p->rightSon = NULL;
    p->balance = 0;
    return p;
}

//Rotate to right
void rightRotation(node** dad){

    node *aux = (*dad)->leftSon;

    (*dad)->leftSon = aux->rightSon;
    aux->rightSon = *dad;
    *dad = aux;
}

//Rotate to left
void leftRotation(node** dad){

    node *aux  = (*dad)->rightSon;

    (*dad)->rightSon = aux->leftSon;
    aux->leftSon = *dad;
    *dad = aux;
}

// Fix balance based on given information
void balanceFix(node* dad, int dependency){

    dad->balance = 0;

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

//Verify and treat a insertion in right subtree
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

//Verify and treat a insertion in left subtree
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

//Verify and treat a removal in left subtree
void treatLeftReduction(node** dad, char* flag){

    (*dad)->balance++;

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

//Verify and treat a removal in right subtree
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

//The real insert node function
void insertNodeR(node** dad, CompPointer userComparator, void* id, char* flag){

    //The function is on leaf, create node and set flag
    if(*dad == NULL){
        *dad = makeNode(id);
        *flag = 1;
    } else {
        switch(userComparator((*dad)->ID, id)){
            //Go to left
            case 1:
                insertNodeR(&(*dad)->leftSon, userComparator, id, flag);
                if(*flag == 1)
                    treatLeftInsertion(&(*dad), flag);
                break;
            //Go to right
            case -1:
            case  0:
                insertNodeR(&(*dad)->rightSon, userComparator, id, flag);
                if(*flag == 1)
                    treatRightInsertion(&(*dad), flag);
                break;
        }
    }
}

//The real remove node function
void removeNodeR(node** dad, CompPointer userComparator, void* id, char* flag){

    //Wrong way
    if(*dad != NULL){

        switch(userComparator((*dad)->ID, id)){
            case 1:
                removeNodeR(&(*dad)->leftSon, userComparator, id, flag);
                if(*flag == 1)
                    treatLeftReduction(&(*dad), flag);
                break;
            case -1:
                removeNodeR(&(*dad)->rightSon, userComparator, id, flag);
                if(*flag == 1)
                    treatRightReduction(&(*dad), flag);
                break;
            case 0:
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
                break;
        }
    }
}
