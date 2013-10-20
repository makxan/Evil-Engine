//
//  GLAppDelegate.h
//  GL
//
//  Created by Viktor Holmqvist on 2011-02-01.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#import <UIKit/UIKit.h>

@class GameViewController;

@interface GLAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    GameViewController *gameViewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) GameViewController *gameViewController;

@end

