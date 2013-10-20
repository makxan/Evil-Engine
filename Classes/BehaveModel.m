//
//  Model.m
//  Phyrax
//
//  Created by Sonny Karlsson on 1/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
/*
#import "BehaveModel.h"
#import "Collision.h"
#import "Shape.h"
#import <stdio.h>
#import "TransformMatrix.h"

static BehaveModel *instance;

@implementation BehaveModel

@synthesize inputController;

+ (id)getInstance{
	if (instance == nil) {
		instance = [[BehaveModel alloc] init];
	}
	return instance;
}

- (id)init
{
    self = [super init];
	if (self)
	{
		InputController *ic = [[InputController alloc] init];
		
		UIAccelerometer *ac = [UIAccelerometer sharedAccelerometer];
		ac.updateInterval   = 0.1;
		ac.delegate         = ic;
		ic.accelerometer    = ac;
		[ac release];
		
		CollideTouch *ct = [[CollideTouch alloc] init];
		ic.collideTouch  = ct;
		[ct release];
		
		self.inputController = ic;
		[ic release];
	}
	return self;
}

- (void)dealloc
{
	[inputController release];
	[super dealloc];
}

// To prevent the standard NSObject to perform standard method such as retain and release,
// we overwrite these methods to make the behaviour proper for a singleton (can not be released).

- (NSUInteger)retainCount {
	return UINT_MAX;
}

- (id)retain {
	return self;
}

- (id)autorelease {
	return self;
}

- (void)release {
	//do nothing
}

- (void)behaviourPhysics:(GameObject *)obj {
	RigidBody *body = [obj getRigidBody];
	
	// Add gravitational force
    Vector2 gravityDirection = (Vector2){inputController.accelerationX, inputController.accelerationY};
    
    //vector2Normalize(&gravityDirection);
    
    Vector2 gravity = gravityDirection;
    
    vector2Scale(&gravity, 6.5f/body->inverseMass);
	
	// Add drag
	// This code is also implemented in DragForce.m and in the future the game will use that class
	//float speed = vector2Magnitude(&(body->velocity));
	
	BOOL touched = [obj getTouched];
	float scale = 1.0f/body->inverseMass;
	if (touched) {
		Vector2 positionVec = getTranslation(body->bodyToWorldMatrix);
		Vector2 touchForce = *[obj getTouchForce];
		vector2Subtract(&touchForce, &positionVec);
		vector2Scale(&touchForce, scale);
		addForce(body, &touchForce);
	}
	else {
		addForce(body, &gravity);
	}

	
	float air = (body->drag)*0.5*(1.2041/1000)*1*speed*speed;
	float water = (body->drag)*0.5*1*1*speed*speed;
	
	Vector2 drag = body->velocity;
	vector2Flip(&drag);
	vector2Normalize(&drag);
	
	vector2Scale(&drag, air);
	
	// Testlog
	//NSLog(@"Drag: Speed: %f x: %f y: %f GravX: %f GravY: %f", speed, drag.x, drag.y);
	addForce(body,&drag);
	
	 
	integrateBody(body, 0.016);
	
}

- (void)behaviourDemoGravity:(GameObject *)obj {
	RigidBody *body = [obj getRigidBody];
	rotate(body->bodyToWorldMatrix, atanf(- inputController.accelerationX / inputController.accelerationY));
	if (inputController.accelerationY > 0.0f)
		rotate(body->bodyToWorldMatrix, M_PI);
	
	rotate(body->bodyToWorldMatrix, M_PI);
}

- (void) behaviorTouch:(GameObject *) obj
{
		RigidBody *body = [obj getRigidBody];
		integrateBody(body, 0.016);
}

@end
*/