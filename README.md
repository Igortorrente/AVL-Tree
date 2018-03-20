# AVL-Tree

## About
 Generic Implementation of  AVL Tree in C

## Requirements
> * stdlib.h
> * stdbool.h
> * string.h
> * compiler compatible with standard C 2011

## API

Initialize the AVL tree.
```  c 
void avlInitializer(AVL* Tree); 
```

Remove all nodes of the AVL tree.
```  c 
void ClearTree(node** No); 
```

Check if AVL tree is empty.
```  c 
bool empty(AVL Tree); 
```

Return the content of the node ID from the AVL tree.
```  c 
void* getnode(AVL Tree, void* id); 
```

Insert a node ID into the AVL tree.
```  c 
void insertNode(AVL* Tree, void* id); 
```

Remove a node ID from the AVL tree.
```  c 
void removeNode(AVL* Tree, void* id); 
```

Check if node ID is on the AVL tree.
```  c 
bool searchNode(AVL Tree, void* id); 
```

Set node comparator function to use on the AVL logic.
```  c 
void setComparator(AVL* Tree, CompPointer userComparator); 
```

## Comparator

##### Model of Comparator
   ``` c 
    int YourComparator(void* A, void* B )
   ```
##### Returns:

|     Return    |    Condition  |
|:-------------:| :------------:| 
|       0       |    A  =  B    | 
|       1       |    A  >  B    |
|      -1       |    A  <  B    |
    
    
