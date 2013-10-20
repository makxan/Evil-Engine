#ifndef __DYNAMIC_ARRAY__
#define __DYNAMIC_ARRAY__

#include <stdlib.h>

#define NOINDEX 0

typedef unsigned int ArrayIndex;

typedef struct {
    char*        array;         // Pointer to array where elements are stored.
    unsigned int arrayUsed;     // Number of elements occupied.
    unsigned int arrayCapacity; // Number of elements allocated.
    unsigned int initCapacity;  // Initial capacity. Used with constant growth.
    unsigned int growthFactor;  // Specify growth factor for array.
    size_t       elemSize;      // Size to allocate for each element.
} DynamicArray;

/* Allocate a new dynamic array.
 * Creates a new dynamic array with space of elements of elemSize
 * that grows with constant amount or based on growthFactor.
 * Note: arrayCapacity remains 0 until first element is added.
 *
 * Arguments:
 * capacity     Initial capacity to allocate.
 * growthFactor Factor for growth, 0 for constant, 1 for double.
 * elemSize     Maximum size of elements.
 */
DynamicArray newArray(unsigned int capacity,
                      unsigned int growthFactor,
                      size_t elemSize);

/* Add element last in array.
 * Copies elemSize data from pointer elem into array and returns index.
 * Note: If no space exists, grows array.
 */
ArrayIndex addLast(DynamicArray* array, 
                   const void* elem, 
                   const size_t elemSize);

/* Writes element at index of array if inside of bounds.
 * Return 1 for a successfull write and 0 for unsuccessfull.
 * Note: Does not allocate space, must be done manually.
 */
int putAtIndex(DynamicArray* array, 
               const ArrayIndex index, 
               const void* elem, 
               const size_t elemSize);

/* Get pointer to element at index.
 * Returns a pointer at element in array, is null if index out of bounds.
 */
void* getAtIndex(const DynamicArray* array, ArrayIndex index);

/* Force growth of array.
 * Allocates more capacity to array based on array settings.
 * Returns 0 for error and 1 for success.
 */
int arrayForceGrow(DynamicArray* array);

/* Force array to shrink.
 * Remove capacity from array based on array settings.
 * Note: Does not check if removed capacity contains elements.
 */
int arrayForceShrink(DynamicArray* array);

/* Soft empty array.
 * Sets used to 0 and preserve capacity.
 */
void arraySoftEmpty(DynamicArray* array);

/* Hard empty array.
 * Sets used to 0 and free capacity.
 * Use: Call before freeing array or memory will leak.
 */
void arrayHardEmpty(DynamicArray* array);

/* Calculate how much used capacity will trigger growth. */
unsigned int arrayNextGrow(const DynamicArray* array);
/* Calculate how much used capacity triggered last growth. */
unsigned int arrayLastGrow(const DynamicArray* array);
/* Returns current capacity. */
unsigned int arrayCapacity(const DynamicArray* array);
/* Returns current used capacity. */
unsigned int arrayUsed(const DynamicArray* array);

/* Performs boolean AND operation on array.
 * Will stop executing on first False or at end of array.
 * Note: Handle empty elements gracefully.
 */

/* Apply function on each element in array.
 */
#define arrayMap(array, func) {                              \
        for (int i = 1; i <= arrayUsed(array); i++)          \
            (*func)(getAtIndex(array, i));                   \
    }


#endif // __DYNAMIC_ARRAY__
