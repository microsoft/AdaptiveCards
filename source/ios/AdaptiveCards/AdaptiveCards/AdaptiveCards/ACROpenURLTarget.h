//
//  ACROpenURLTarget
//  ACROpenURLTarget.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <SafariServices/SafariServices.h>
#import <UIKit/UIKit.h>

@interface ACROpenURLTarget:NSObject<SFSafariViewControllerDelegate, UIGestureRecognizerDelegate>

- (instancetype)initWithURL:(NSURL *)url viewController:(UIViewController *)vc;

- (instancetype)initWithURL:(NSURL *)url viewController:(UIViewController *)vc targetView:(UIView *)view;

- (IBAction)openURL;

- (IBAction)openURL:(UILongPressGestureRecognizer *) recognizer;

@end
