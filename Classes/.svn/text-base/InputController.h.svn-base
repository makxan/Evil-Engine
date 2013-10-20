//
//  InputController.h
//  GL
//
//  Created by Viktor Holmqvist on 2011-02-04.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CollideTouch.h"

@interface InputController : UIResponder <UIAccelerometerDelegate> {
	float accelerationX;
	float accelerationY;
	
	LinkedNode *positions;
	LinkedNode *previous;
	
	UIAccelerometer *accelerometer;
	
	CollideTouch *collideTouch;
	
	CGPoint startPoint;
	CGFloat initialDistance;
	//GLfloat rotationAngle;
	NSTimer *timer;
}

@property float accelerationX;
@property float accelerationY;

@property (nonatomic, retain) UIAccelerometer *accelerometer;
@property (nonatomic, retain) CollideTouch *collideTouch;

@end
