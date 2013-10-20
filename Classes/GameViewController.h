//
//  GameViewController.h
//  GL
//
//  Created by Viktor Holmqvist on 2011-02-01.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//	
//	Main viewcontroller.
//

#import <UIKit/UIKit.h>
#import "EvilShapes.h"
#import <OpenGLES/EAGL.h>

@class GLViewController;

@interface GameViewController : UIViewController {
	EAGLContext *context;
	
	BOOL animating;
    NSInteger animationFrameInterval;
    CADisplayLink *displayLink;
	
	EvilGameState state;
}

@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) CADisplayLink *displayLink;
@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;
- (void)startAnimation;
- (void)stopAnimation;
- (void)startGame;
@end
