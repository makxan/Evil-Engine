//
//  LinkedListTests.m
//  GL
//
//  Created by Sonny Karlsson on 3/15/11.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#import "LinkedListTests.h"
#import "LinkedList.h"

int compare(const void *arg1, const void *arg2) {
	if ((int)arg1 < (int)arg2)
		return 1;
	else 
		return 0;
}

@implementation LinkedListTests

- (void) testMath {
    
	STAssertTrue(NULL == 0, @"NULL IS 0");
	
	LinkedNode* list = NULL;
	
	int (*ptr)(const void *, const void *);
	ptr = compare;

    for (int i = 1; i < 5; i++) {
		pushSortedOnNode(&list, (void *)i, ptr);
	}
	int i = 1;
	for (LinkedNode *node = list; node != NULL; node = node->next, i++) {
		STAssertTrue(i == (int)(node->element), @"%i == %i", i, (int)(node->element));
	}
	
	deallocList(list);
	list = NULL;
	
    for (int i = 4; i > 0; i--) {
		pushSortedOnNode(&list, (void *)(i), ptr);
	}
	i = 1;
	for (LinkedNode *node = list; node != NULL; node = node->next, i++) {
		STAssertTrue(i == (int)(node->element), @"%i == %i", i, (int)(node->element));
	}
	
	deallocList(list);
	list = NULL;
	
	int es[] = {1,1,2,2,2,3,3,4,4,5,7}; // Is sorted of:
	int is[] = {2,3,4,3,7,5,4,2,1,1,2};
	
	for (int i = 0; i < sizeof(is) / sizeof(int); i++) {
		pushSortedOnNode(&list, (void *)(is[i]), ptr);
	}
	
	i = 0;
	for (LinkedNode *node = list; node != NULL; node = node->next, i++) {
		STAssertTrue(es[i] == (int)(node->element), @"%i == %i", es[i], (int)(node->element));
	}
}

@end


