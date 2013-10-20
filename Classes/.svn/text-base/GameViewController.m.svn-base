    //
//  GameViewController.m
//  GL
//
//  Created by Viktor Holmqvist on 2011-02-01.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "EAGLView.h"
#import "GameViewController.h"
#import "Benchmarking.h"
#import "SceneModel.h"

static const GLfloat squareVertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
	0.5f,  0.5f, 0.0f,
};

static const GLubyte squareColors[] = {
	255, 255,   0, 255,
	0,   255, 255, 255,
	0,     0,   0,   0,
	255,   0, 255, 255,
};

@implementation GameViewController
@synthesize animating, displayLink, context;

// Send UI actions to the input controller
/*
- (UIResponder *)nextResponder {
	return [[BehaveModel getInstance] inputController];
}
*/
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
	
	EAGLView *eaglView = [[EAGLView alloc] initWithFrame:[UIScreen mainScreen].applicationFrame];
	self.view = eaglView;
	[eaglView release];

    GLVersion version = ES2;
    EAGLContext *aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (!aContext)
    {
		version = ES1;
        aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    }
	//Start with OpenGLES1
	//EAGLContext *aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    //GLVersion version = ES1;
	// Start with OpenGLES2
	//EAGLContext *aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
	//GLVersion version = ES2; 
    if (!aContext)
        NSLog(@"Failed to create ES context");
    else if (![EAGLContext setCurrentContext:aContext])
        NSLog(@"Failed to set ES context current");
    
	self.context = aContext;
	[aContext release];
	
    [(EAGLView *)self.view setContext:context];
    [(EAGLView *)self.view setFramebuffer];
	
	// Set retina resolution for current view.
	CAEAGLLayer *eaglLayer = (CAEAGLLayer *)((EAGLView *)self.view).layer;
	eaglLayer.contentsScale = [UIScreen mainScreen].scale;
	
	animating = FALSE;
    animationFrameInterval = 1;
    self.displayLink = nil;
	
	CGSize screenSize = [UIScreen mainScreen].applicationFrame.size;
	state = newEvilState();
	initEvilState(&state, version, screenSize.height, screenSize.width);
	
	[self startGame];
}

- (void)startGame {
    addFourWalls(&state);
    addHShape(&state);
    //addSquareShape(&state);
}

- (void)update {
	
	nextEvilState(&state);
	
	[(EAGLView *)self.view setFramebuffer];
	
	drawEvilState(&state);
	
	[(EAGLView *)self.view presentFramebuffer];
}

- (NSInteger)animationFrameInterval
{
    return animationFrameInterval;
}

- (void)viewWillAppear:(BOOL)animated
{
    [self startAnimation];
    
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self stopAnimation];
    
    [super viewWillDisappear:animated];
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
    /*
	 Frame interval defines how many display frames must pass between each time the display link fires.
	 The display link will only fire 30 times a second when the frame internal is two on a display that refreshes 60 times a second. The default frame interval setting of one will fire 60 times a second when the display refreshes at 60 times a second. A frame interval setting of less than one results in undefined behavior.
	 */
    if (frameInterval >= 1)
    {
        animationFrameInterval = frameInterval;
        
        if (animating)
        {
            [self stopAnimation];
            [self startAnimation];
        }
    }
}

- (void)startAnimation
{
    if (!animating)
    {
        CADisplayLink *aDisplayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
        [aDisplayLink setFrameInterval:animationFrameInterval];
        [aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        self.displayLink = aDisplayLink;
        
        animating = TRUE;
    }
}

- (void)stopAnimation
{
    if (animating)
    {
        [self.displayLink invalidate];
        self.displayLink = nil;
        animating = FALSE;
    }
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
	// Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
	self.context = nil;	
}


- (void)dealloc {
	destroyEvilState(&state);
	
	if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
    [context release];
    [super dealloc];
}


@end
