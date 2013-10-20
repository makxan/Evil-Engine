//
//  BinaryHeap.h
//  GL
//
//  Created by Robin Rye on 3/30/11.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#ifndef BINARYHEAP
#define BINARYHEAP
typedef struct Heap {
    int (*func)(void*, void*);
    int capacity;
    int size;
    void** elems;
    
} Heap;

Heap* init(int maxSize, int (*order)(void*, void*));
void deallocHeap(Heap* h);
void makeEmpty(Heap* h);
// Insertion
int insertElement(void* obj, Heap* h);

void* popRoot(Heap* h);
void* peakRoot(Heap* h);
int isEmpty(Heap* h);
int isFull(Heap* h);

int max(void*, void*);
int min(void*, void*);

#endif











