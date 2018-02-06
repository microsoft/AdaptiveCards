//
//  ACROpenURLTarget
//  ACROpenURLTarget.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "ACRLongPressGestureRecognizerEventHandler.h"

@interface ACROpenURLTarget:NSObject<ACRSelectActionDelegate>

- (instancetype)initWithURL:(NSURL *)url viewController:(UIViewController *)vc;

- (IBAction)openURL;

@end
