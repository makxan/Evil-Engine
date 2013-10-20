/*
 *  DynamicArray.c
 *  GL
 *
 *  Created by Sonny Karlsson on 3/22/11.
 *  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
 *
 */

#include "DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#undef DEBUG

/* Create a new dynamic array.
 * Creates a new dynamic array with space for elements of elemSize
 * that grows with constant capacity or by doubling capacity.
 *
 * Arguments:
 * capacity     Initial capacity to allocate.
 * growthFactor Factor for growth, 0 for constant, 1 for double.
 * elemSize     Maximum size of elements.
 */
DynamicArray newArray(unsigned int capacity,
                      unsigned int growthFactor,
                      size_t elemSize)
{
    assert(elemSize > 0);
    assert(capacity > 0);

    return (DynamicArray){
        .arrayCapacity = 0, 
        .arrayUsed     = 0, 
        .growthFactor  = growthFactor, 
        .initCapacity  = capacity, 
        .elemSize      = elemSize, 
        .array         = NULL
    };
}

/* Add element last in array.
 * Copies elemSize data from pointer elem into array and returns index.
 * Note: If no space exists, grows array.
 */
ArrayIndex addLast(DynamicArray* array, 
                   const void* elem, 
                   const size_t elemSize)
{
    if (elem == NULL) {
        printf("addLast: Tried to add NULL.\n");
    }
    const ArrayIndex index = array->arrayUsed + 1;
    if (putAtIndex(array, index, elem, elemSize) == 0) {
        arrayForceGrow(array);
        if (putAtIndex(array, index, elem, elemSize) == 0) {
            printf("addLast: Failed to add to array.\n");
            return 0;
        }
    }
    return index;
}

/* Writes element at index of array if inside of capacity bounds.
 * Return 1 for a successfull write and 0 for unsuccessfull.
 * Will set array used to index if index exceeds previous used.
 * Note: Does not allocate space, must be done manually.
 * Note: Can cause fragmentation in array.
 * Note: Care is taken to initialize capacity if framentation occur.
 */
int putAtIndex(DynamicArray* array, 
               const ArrayIndex index, 
               const void* elem, 
               const size_t elemSize)
{
    #ifdef DEBUG
    if (elem == NULL) {
        printf("putAtIndex: Tried to add NULL.\n");
        return 0;
    } else if (index == 0) {
        printf("putAtIndex: Tried to add on index 0.\n");
        return 0;
    } else if (array->arrayCapacity < index) {
        printf("putAtIndex: Not enough capacity for index, %d.\n", index);
        return 0;
    } else if (array->array == NULL) {
        printf("putAtIndex: Array uninitiated.\n");
        return 0;
    }
    #else
    if (elem == NULL || array->array == NULL || 
        index == 0 || array->arrayCapacity < index)
        return 0;
    #endif

    char* ptrToIndex = array->array + (index - 1) * array->elemSize;
    memcpy(ptrToIndex, elem, elemSize);

    if (array->arrayUsed == index - 1) {
        array->arrayUsed = index;
    } else if (array->arrayUsed < index) {
        char* ptrToUsed   = array->array + (array->arrayUsed * array->elemSize);
        memset(ptrToUsed, 0, ptrToIndex - ptrToUsed);
        #ifdef DEBUG
        printf("putAtIndex: Overwriting %d bytes with zeros.\n", ptrToIndex - ptrToUsed);
        #endif
        array->arrayUsed = index;
    }
    return 1;
}

/* Get pointer to element at index.
 * Returns a pointer at element in array, is null if index out of capacity.
 */
void* getAtIndex(const DynamicArray* array, ArrayIndex index)
{
    if (index == 0 || array->arrayUsed < index) {
        #ifdef DEBUG
        printf("getAtIndex: Index 0 or outside capacity, %d.\n", index);
        #endif
        return NULL;
    }
    return (void*)(array->array + ((index - 1) * array->elemSize));
}

/* Force growth of array.
 * Allocates more capacity to array based on array settings.
 * Returns 0 for error and 1 for success.
 */
int arrayForceGrow(DynamicArray* array)
{
    unsigned int newCapacity = array->arrayCapacity;

    if (array->growthFactor == 0)
        newCapacity += array->initCapacity;
    else if (newCapacity == 0)
		newCapacity += array->initCapacity;
	else
        newCapacity *= 2;

    char* newArray = realloc(array->array, newCapacity * array->elemSize);
    if (newArray == NULL) {
        printf("arrayForceGrow: Can't grow array further.\n");
        return 0;
    }
    
    array->array         = newArray;
    array->arrayCapacity = newCapacity;
    return 1;
}

/* Force array to shrink.
 * Remove capacity from array based on array settings.
 * Return 0 for error and 1 for success.
 * Note: Does not check if removed capacity contains elements.
 */
int arrayForceShrink(DynamicArray* array)
{
    unsigned int newCapacity = arrayLastGrow(array);

    if (newCapacity == 0) {
        free(array->array);
        array->array = NULL;
        return 1;
    } 
    
    void* newArray = realloc(array->array, newCapacity * array->elemSize);
    if (newArray == NULL) {
        printf("arrayForceShrink: Can't shrink array... WTF.");
        return 0;
    }

    array->array         = newArray;
    array->arrayCapacity = newCapacity;
    if (array->arrayUsed > newCapacity)
        array->arrayUsed = newCapacity;
    return 1;
}

/* Soft empty array.
 * Sets used to 0 and preserve capacity.
 */
void arraySoftEmpty(DynamicArray* array) {
    array->arrayUsed = 0;
}

/* Hard empty array.
 * Sets used to 0 and free capacity.
 */
void arrayHardEmpty(DynamicArray* array) {
    free(array->array);
    array->array         = NULL;
    array->arrayCapacity = 0;
    array->arrayUsed     = 0;
}

/* Calculate how much used capacity triggered last growth. 
 * Note: Used by arrayForceShrink to determine new capacity.
 * Note: If x has rem then something is wrong.
 * Note: Black magic bit twiddling log2 implementation.
 */
unsigned int arrayLastGrow(const DynamicArray* array) 
{
    const div_t x = div(array->arrayCapacity, array->initCapacity);
    unsigned int quot = x.quot;
    unsigned int r    = 0;

    assert(x.rem == 0);

    if (array->growthFactor != 0) {
        while (quot >>= 1)
            r++;
        assert(r != 0);
        return (2^(r-1) * array->initCapacity);
    } else {
        assert(quot > 0);
        return ((quot-1) * array->initCapacity);
    }
}

/* Returns current capacity. */
unsigned int arrayCapacity(const DynamicArray* array)
{
    return array->arrayCapacity;
}
/* Returns current used capacity. */
unsigned int arrayUsed(const DynamicArray* array) {
    return array->arrayUsed;
}
