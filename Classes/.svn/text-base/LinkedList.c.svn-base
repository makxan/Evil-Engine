
#include "LinkedList.h"

#include <stdlib.h>

/*
 Example looping:
 
 >> LinkedNode *root;
 >>
 >>for (LinkedNode *node = root; node != NULL; node = node->next) {
 >>	Shape *element = (Shape *)(node->element);
 >>	// do stuff with element.
 >>}
 */

// O(1) add element at front on linked list.
void pushOnNode(LinkedNode **root, const void *element)
{
	LinkedNode *node = malloc(sizeof(LinkedNode));
	node->element = (void *)element;
	node->next = *root;
	*root = node;
}

// Add element to the list and place it according to the sorting function. Assumes that the rest of the list is sorted.
void pushSortedOnNode(LinkedNode **root, const void *element, int (*compare)(const void *, const void *))
{    
    if(*root == NULL) {
        pushOnNode(root, element);
		return;
	}
	
	LinkedNode *previous = NULL;
	
	LinkedNode *newNode = malloc(sizeof(LinkedNode));
	newNode->element = (void *)element;
	newNode->next    = NULL;
    
	for (LinkedNode *node = *root; node != NULL; node = node->next) {
		if(compare(element, node->element) == 1) {
			newNode->next = node;
			if (previous != NULL) {
				previous->next = newNode;
            } else
                *root = newNode;
			return;
		} else if (node->next == NULL) {
			node->next = newNode;
			return;
		} else
			previous = node;
	}
}

// O(1) get first element of linked list.
// Assumes that root is not null,
// may be null after.
void *popOfNode(LinkedNode *root)
{
	LinkedNode *node = root->next;
	void *element = (root->element);
	free(node);
	return element;
}

// Delete first node with same element address
// Return 1 on success, 0 on failure.
// Worst case O(N), average O(log N).
int deleteOfNode(LinkedNode *root, const void *element)
{
	LinkedNode *node;
	for (node = root; node->next != NULL && node->next->element != element; node = node->next) {}
	if (node->next != NULL) {
		LinkedNode *doomed = node->next;
		node->next = doomed->next;;
		free(doomed);
		return 1;
	} else
		return 0;
}

int listContains(LinkedNode *root, const void *element)
{
	LinkedNode *node;
	for (node = root; node->next != NULL && node->next->element != element; node = node->next) {}
	if (node->next != NULL) {
		return 1;
	} else
		return 0;
}

// Dealloc all nodes in list after root.
void deallocList(LinkedNode *root)
{
	LinkedNode *node1;
	LinkedNode *node2;
	for (node1 = root; node1 != NULL; node1 = node2->next) {
        node2 = node1;
        free(node1);
	}
	root = NULL;
}