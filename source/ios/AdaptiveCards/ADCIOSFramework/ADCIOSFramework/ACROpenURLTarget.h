//
//  ACROpenURLTarget
//  ACROpenURLTarget.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ACROpenURLTarget:NSObject

- (instancetype)initWithURL:(NSURL *)url viewController:(UIViewController *)vc;

- (IBAction)openURL;

@end
