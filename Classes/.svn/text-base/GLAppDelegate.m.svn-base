//
//  GLAppDelegate.m
//  GL
//
//  Created by Viktor Holmqvist on 2011-02-01.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#import "GLAppDelegate.h"
#import "GameViewController.h"

@implementation GLAppDelegate

@synthesize window;
@synthesize gameViewController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	UIWindow *w = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].applicationFrame];
	self.window = w;
	[w release];
	
	GameViewController *vc = [[GameViewController alloc] init];
	self.gameViewController = vc;
	[vc release];
    [self.window addSubview:self.gameViewController.view];
	[window makeKeyAndVisible];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    [self.gameViewController stopAnimation];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [self.gameViewController startAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    [self.gameViewController stopAnimation];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Handle any background procedures not related to animation here.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Handle any foreground procedures not related to animation here.
}

- (void)dealloc
{
    [gameViewController release];
    [window release];
    
    [super dealloc];
}

@end
