//
//  CollideTouch.m
//  GL
//
//  Created by Sonny Karlsson on 2/25/11.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#import "CollideTouch.h"
#import "Collision.h"
#import "Shape.h"
#import "LinkedList.h"


@implementation CollideTouch
@synthesize gameObjects;

- (id)init 
{
    self = [super init];
	if (self) {
		objectList = [[NSMutableArray alloc] init];
		gameObjects = [[NSMutableDictionary alloc] init];
	}
	return self;
}

- (void)dealloc
{
	[objectList release];
	[super dealloc];
}

- (void)addToRegister:(id<Collidable, Touchable>)obj
{
	[objectList addObject:obj];
}
- (void)delFromRegister:(id<Collidable, Touchable>)obj
{
	[objectList removeObjectIdenticalTo:obj];
}


- (void)collideWithTouch:(LinkedNode *)positions
{
	for(LinkedNode *position = positions; position != NULL; position = position->next){
		Point2 *p = (Point2 *) position->element;
	
        for (int i = 0; i < [objectList count]; i++) {
            GameObject *obj = [objectList objectAtIndex:i];
            RigidBody *body = [obj getRigidBody];
		
            for (LinkedNode *node = body->shapes; node != NULL; node = node->next) {
                SShape *shape = (SShape *)node->element;
                if (containsPoint(body->bodyToWorldMatrix, shape, *p)) {
                    [obj handleTouch:p];
                    float x = p->x; 
                    float y = p->y;
                    [gameObjects setObject:obj forKey:[NSString stringWithFormat:@"%f%f", x, y]];
                }
            }
        }
	}
}

- (void)moveWithTouch:(LinkedNode *)positions withPreviousLocations:(LinkedNode *)previous
{
	LinkedNode *position = positions;
	
	for (LinkedNode *prev = previous; prev != NULL && position != NULL; prev = prev->next, position = position->next) {
		Point2 *p = (Point2 *) prev->element;
		Point2 *pos = (Point2 *) position->element; 
		
		float x = p->x;
		float y = p->y;
		
		float xPos = pos->x;
		float yPos = pos->y;
		
		NSString *key = [NSString stringWithFormat:@"%f%f", x, y];
		
		GameObject *obj = [gameObjects objectForKey:key];
		
		if (obj != nil) {
			[obj handleTouch:pos];
			[gameObjects setObject:obj forKey:[NSString stringWithFormat:@"%f%f", xPos, yPos]];
			[gameObjects removeObjectForKey:key];
			
		}
		else {
			[self collideWithTouch:position];
		}
	}
	
}

- (void)endTouch:(LinkedNode *)positions withPrevious:(LinkedNode *)previous
{
	LinkedNode *position = positions;
	
	for (LinkedNode *prev = previous; prev != NULL && position != NULL; prev = prev->next, position = position->next) {
		Point2 *p = (Point2 *) prev->element;
		Point2 *pos = (Point2 *) position->element; 
		
		float x = p->x;
		float y = p->y;
		
		float xPos = pos->x;
		float yPos = pos->y;
		
		NSString *key1 = [NSString stringWithFormat:@"%f%f", x, y];
		NSString *key2 = [NSString stringWithFormat:@"%f%f", xPos, yPos];
		
		GameObject *obj = [gameObjects objectForKey:key1];
		
		if (obj != nil) {
			[obj handleTouchEnded:p];
			[gameObjects removeObjectForKey:key1];
			
		}
		
		obj = [gameObjects objectForKey:key2];
		
		if (obj != nil) {
			[obj handleTouchEnded:pos];
			[gameObjects removeObjectForKey:key2];
			
		}
	}
}

@end
