//
//  CollideTouch.h
//  GL
//
//  Created by Sonny Karlsson on 2/25/11.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#import <Foundation/Foundation.h>
#import	"Touchable.h"
#import "Collidable.h"
#import "Vector.h"
#import "GameObject.h"
#import "LinkedList.h"


@interface CollideTouch : NSObject {
	
	NSMutableDictionary *gameObjects;
	
	NSMutableArray *objectList;
}

@property (nonatomic, retain) NSDictionary *gameObjects;

// Add or remove object from this collision generator.
- (void)addToRegister:(id<Collidable, Touchable>)obj;
- (void)delFromRegister:(id<Collidable, Touchable>)obj;

- (void)collideWithTouch:(LinkedNode *)positions;
- (void)moveWithTouch:(LinkedNode *)positions withPreviousLocations:(LinkedNode *)previous;
- (void)endTouch:(LinkedNode *)positions withPrevious:(LinkedNode *)previous;

@end
