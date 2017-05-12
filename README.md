# AVL-Tree

## About
 Generic Implementation of  AVL Tree in C

## Requirements
> * stdlib.h
> * stdbool.h
> * string.h
> * compiler compatible with standard C 2011

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
    
    
