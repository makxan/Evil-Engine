//
//  InputController.m
//  GL
//
//  Created by Viktor Holmqvist on 2011-02-04.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#import "InputController.h"
#import "GLAppDelegate.h"

@implementation InputController
@synthesize accelerationX, accelerationY, accelerometer, collideTouch;

- (id)init
{
    self = [super init];
	if (self) {
		positions = NULL;
		previous = NULL;
	}
	return self;
}

- (CGFloat)distanceBetweenTwoPoints:(CGPoint)fromPoint toPoint:(CGPoint)toPoint {
	float x = toPoint.x - fromPoint.x;
	float y = toPoint.y - fromPoint.y;
	
	return sqrt(x * x + y * y);
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	UIView *view = ((GLAppDelegate *)[[UIApplication sharedApplication] delegate]).window;
	
	NSArray *allTouches = [touches allObjects];
	
	for (int i = 0; i < [allTouches count]; i++){
		UITouch *theTouch = [allTouches objectAtIndex:i];
		
		startPoint = [theTouch locationInView:view];
		
		float x = startPoint.x;
		float y = startPoint.y;
		
		x = (x - ([UIScreen mainScreen].applicationFrame.size.width/2)) / 50;
		y = -((y - ([UIScreen mainScreen].applicationFrame.size.height/2)) / 50);
		
		Point2 *position = malloc(sizeof(Point2));
		*position = (Point2) {x, y};
		
		pushOnNode(&positions, (void *) position);
	}
	
	[collideTouch collideWithTouch: positions];
}

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
	UIView *view = ((GLAppDelegate *)[[UIApplication sharedApplication] delegate]).window;
	
	NSArray *allTouches = [touches allObjects];
	
	for(int i = 0; i < [allTouches count]; i++) {
		UITouch *theTouch = [allTouches objectAtIndex:i];
		
		CGPoint touchLocation = [theTouch locationInView:view];
		CGPoint prevLocation = [theTouch previousLocationInView:view];

		float xPos = touchLocation.x;
		float yPos = touchLocation.y;
		
		float xPrev = prevLocation.x;
		float yPrev = prevLocation.y;
		
		xPos = (xPos - ([UIScreen mainScreen].applicationFrame.size.width/2)) / 50;
		yPos = -((yPos - ([UIScreen mainScreen].applicationFrame.size.height/2)) / 50);
		
		xPrev = (xPrev - ([UIScreen mainScreen].applicationFrame.size.width/2)) / 50;
		yPrev = -((yPrev - ([UIScreen mainScreen].applicationFrame.size.height/2)) / 50);
		
		Point2 *position = malloc(sizeof(Point2));
		*position = (Point2) {xPos, yPos};
		
		pushOnNode(&positions, (void *) position);
		
		Point2 *prev = malloc(sizeof(Point2));
		*prev = (Point2) {xPrev, yPrev};
		
		pushOnNode(&previous, (void *) prev);
	}
	
	[collideTouch moveWithTouch:positions withPreviousLocations:previous];
	
    Point2 *point;
    for (LinkedNode *node = positions; node != NULL; node = node->next) {
		point = (Point2 *)(node->element);
		free(point);
	}

    for (LinkedNode *node = previous; node != NULL; node = node->next) {
		point = (Point2 *)(node->element);
		free(point);
	}
    
    deallocList(positions);
    deallocList(previous);
    
	positions = NULL;
	previous = NULL;
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	UIView *view = ((GLAppDelegate *)[[UIApplication sharedApplication] delegate]).window;
	
	NSArray *allTouches = [touches allObjects];
	
	for(int i = 0; i < [allTouches count]; i++) {
		UITouch *theTouch = [allTouches objectAtIndex:i];
		
		CGPoint touchLocation = [theTouch locationInView:view];
		CGPoint prevLocation = [theTouch previousLocationInView:view];
		
		float xPos = touchLocation.x;
		float yPos = touchLocation.y;
		
		float xPrev = prevLocation.x;
		float yPrev = prevLocation.y;
		
		xPos = (xPos - ([UIScreen mainScreen].applicationFrame.size.width/2)) / 50;
		yPos = -((yPos - ([UIScreen mainScreen].applicationFrame.size.height/2)) / 50);
		
		xPrev = (xPrev - ([UIScreen mainScreen].applicationFrame.size.width/2)) / 50;
		yPrev = -((yPrev - ([UIScreen mainScreen].applicationFrame.size.height/2)) / 50);
		
		Point2 *position = malloc(sizeof(Point2));
		*position = (Point2) {xPos, yPos};
		
		pushOnNode(&positions, (void *) position);
		
		Point2 *prev = malloc(sizeof(Point2));
		*prev = (Point2) {xPrev, yPrev};
		
		pushOnNode(&previous, (void *) prev);
	}
	
	[collideTouch endTouch:positions withPrevious:previous];
	
    Point2 *point;
    for (LinkedNode *node = positions; node != NULL; node = node->next) {
		point = (Point2 *)(node->element);
		free(point);
	}
    
    for (LinkedNode *node = previous; node != NULL; node = node->next) {
		point = (Point2 *)(node->element);
		free(point);
	}
    
    deallocList(positions);
    deallocList(previous);
    
	positions = NULL;
	previous = NULL;
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration {
	accelerationX = acceleration.x;
	accelerationY = acceleration.y;
}

- (void)dealloc
{
	[accelerometer release];
	[super dealloc];
}

@end
