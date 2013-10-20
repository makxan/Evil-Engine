//
//  HashMapTests.m
//  GL
//
//  Created by Sonny Karlsson on 3/23/11.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#import "HashMapTests.h"
#import "HashMap.h"
#import <stdlib.h>


@implementation HashMapTests

- (void) testHashMap {
    
    HashMap map = newHashMap(1024);
	
	int r;
	int n = map.length;
	
	for (int i = 0; i < 500; i++) {
		r = abs(arc4random());
		STAssertTrue(insertEntry(&map, r, NULL) != -1, @"insert failed");
		
		if (map.length > n) {
			n = map.length;
			STFail(@"HashMap resized to %i", n);
		}
	}
}


- (void) testHashMapMany {
    HashMap map;
	
	int r;
	int n;
	int a = 0;
	for (int j = 0; j < 1000; j++) {
	    map = newHashMap(1024);
		n   = map.length;
		
		for (int i = 0; i < 512; i++) {
			r = abs(arc4random());
			STAssertTrue(insertEntry(&map, r, NULL) != -1, @"insert failed");
			
			if (map.length > n) {
				a++;
				n = map.length;
				STFail(@"HashMap resized to %i", n);
			}
		}
		
		deallocHashMap(&map);
	}
}

@end
