//
//  BinaryHeap.c
//  GL
//
//  Created by Robin Rye on 3/30/11.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#include "BinaryHeap.h"
#include <stdlib.h>

/*
 * Initalize a heap with max size maxSize.
 */
Heap* init(int maxSize, int (*order)(void*, void*))
{
    //alloc memory for the heap.
    Heap* h = malloc(sizeof(Heap));
    
    //alloc memory for the elements in contained by the heap
    
    h->elems = malloc((maxSize) * sizeof(int));
    
    //set parameters.
    h->capacity = maxSize;
    h->size     = 0;
    h->func     = order;
    
    return h;
}

/*
 * Ignore all elems added before and just set the size to 0 again and set the empty flag.
 */
void makeEmpty(Heap* h)
{
    h->size = 0;
}

/*
 * Insert an object from the bottom an perculate it up til it is at the right level.
 * uses function pointer to generalize max and min heap.
 */
int insertElement(void* elem, Heap* h)
{
    //can't insert if full, return elems[0] which is fault value.
    if(isFull(h))
        return 0;
    
    int i;
    //check if added elem should be moved upward in tree structure.
    for(i = h->size++; i != 0 && h->func(elem, h->elems[i/2]); i /= 2){
        h->elems[i] = h->elems[i/2];
    }
    h->elems[i] = elem;
    return 1;
}

/*
 * Get and delete the root node and move the right node up to the depth-level above.
 */
void* popRoot(Heap* h)
{
    if(isEmpty(h))
        return NULL;
    
    void* rootNode; 
    void* lastNode;
    
    //store rootNode which is to be returned once sorting is done.
    rootNode = h->elems[0];
    //decrement the size of the heap.
    lastNode = h->elems[--h->size];
    
    int next = 1;
    //move the right node up to the depth level above by 
    for(int child = next; child < h->size; child = next){
        //if there are 2 children, choose the one that should be moved up if less than rootNode.
        if(h->func(h->elems[child + 1], h->elems[child]))
            child++;
        
        //if last node should be moved up we are done, otherwise move up child
        if(h->func(h->elems[child], lastNode)){
            //-1 + child % 2 to ensure that left or right child is moved to parent node.
            h->elems[(child/2) - 1 + child % 2] = h->elems[child];
            next = child * 2 + 1;
        }
        else{
            break;
        }
    }
    
    //last node should always be moved either up or to the left sibling.
    h->elems[(next-1)/2] = lastNode;
    //return the rootNode which is either max or min depending on sorting of heap.
    return rootNode;
}

/*
 * returns the min/max elem depending on if it is min/max heap.
 */
void* peakRoot(Heap* h)
{
    if(!isEmpty(h))
        return h->elems[0];
    return NULL;
}


/*
 * if size = 0 the heap is empty.
 */
int isEmpty(Heap* h)
{
    return h->size == 0;
}

/*
 * size = capacity means the heap is full.
 */
int isFull(Heap* h)
{   
    return h->capacity == h->size;
}


/*
 * Free up used memory when done with heap.
 */
void deallocHeap(Heap* h)
{
    free(h->elems);
    free(h);
}

/*
 * function use to sort the heap, either the function pointer in the Heap structure is max-function
 */
int max(void* a, void* b)
{
    return (int)a > (int)b;
}

/*
 * or min-function
 */
int min(void* a, void* b)
{
    return (int)a < (int)b;
}














