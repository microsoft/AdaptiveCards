//
//  ACRViewController.h
//  ACRViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACRActionDelegate.h"

@interface ACRViewController :UIViewController

@property NSString* jsonString;
@property (weak) id<ACRActionDelegate> acrActionDelegate;

- (instancetype)init:(NSString* )str withFrame:(CGRect)frame;

@end
