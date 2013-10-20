
#ifndef LINKEDLIST
#define LINKEDLIST

typedef struct LinkedNode {
	void *element;
	struct LinkedNode *next;
} LinkedNode;

// O(1) add element at front on linked list.
void pushOnNode(LinkedNode **root, const void *element);

void pushSortedOnNode(LinkedNode **root, const void *element, int (*compare)(const void *, const void *));

// O(1) get first element of linked list.
void *popOfNode(LinkedNode *root);

// Delete node with same element address
// Worst case O(N), average O(log N).
int deleteOfNode(LinkedNode *root, const void *element);

// Dealloc all nodes in List
void deallocList(LinkedNode *root);

int listContains(LinkedNode *root, const void *element);

#endif