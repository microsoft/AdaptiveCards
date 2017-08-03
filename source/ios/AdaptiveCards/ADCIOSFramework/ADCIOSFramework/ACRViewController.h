//
//  ACRViewController.h
//  ACRViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACRSubmitActionDelegate.h"

@interface ACRViewController :UIViewController

@property NSString* jsonString;
@property id<ACRSubmitActionDelegate> acrSubmitActionDelegate;
- (instancetype)init:(NSString* )str withFrame:(CGRect)frame;

@end
