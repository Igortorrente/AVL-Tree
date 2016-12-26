#include <stdio.h>
#include "AVL.h"

int ExampleComparator(void *a, void *b){
    if(*((int*)a) > *((int*)b))
        return 1;
    else if (*((int*)a) == *((int*)b))
        return 0;
    else
        return -1;
}

/*
int ExampleComparator(void* a, void* b){
    int retorno = strcmp((char*)a, (char*)b);

    if (retorno > 0)
        return 1;
    else if (retorno < 0)
        return -1;
    else
        return 0;
}
*/

//TODO: Coment this code
int main(){

    char leitura[2];
    int num_comandos, id , i;
    void* aux;


    AVL ExampleTree;
    avlInitializer(&ExampleTree);
    setComparator(&ExampleTree, (CompPointer) ExampleComparator);

    scanf("%d", &num_comandos);

    for(i = 0; i < num_comandos; i++){

        scanf(" %c", &leitura[0]);
        switch(leitura[0]){
            case 'r':
                scanf(" %d", &id);
                removeNode(&ExampleTree, &id);
                printf("\n=======================================\n\n");
                printTree(ExampleTree.avlTree, 0, altura(ExampleTree.avlTree));
                break;
            case 'i':
                scanf(" %d", &id);
                insertNode(&ExampleTree, &id);
                printf("\n=======================================\n\n");
                printTree(ExampleTree.avlTree, 0, altura(ExampleTree.avlTree));
                break;
            case 's':
                scanf(" %d", &id);
                if(searchNode(&ExampleTree, &id))
                    printf("Found\n");
                else
                    printf("Not found\n");
                break;
            case 'g':
                scanf(" %d", &id);
                aux = getnode(&ExampleTree, &id);
                if(aux != NULL)
                    printf("Content %d \n", *((int*)aux));
                else
                    printf("Node not found\n");
                break;
            case 'e':
                destroyTree(&(ExampleTree.avlTree));
                return 0;
            default:
                printf("%c invalid command. Try r,i,e or s\n", leitura[0]);
                break;
        }
        printf("\nComand : ");
    }

    destroyTree(&(ExampleTree.avlTree));

    return 0;
}


