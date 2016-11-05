#include <stdio.h>
#include "AVL.h"

//TODO: Coment this code
int main()
{
    char flag, leitura[2];
    unsigned int num_comandos, id ,i;
    node* avlTree = NULL;

    scanf("%u", &num_comandos);

    for(i = 0; i < num_comandos; i++)
    {
        scanf(" %c %u", &leitura[0], &id);
        if(leitura[0] == 'r')
            removeNode(&avlTree, &flag, id);
        else
            insertNode(&avlTree, id, 15, &flag);
    }
    printTree(avlTree, 0, altura(avlTree));

    destroyTree(&avlTree);

    return 0;
}


