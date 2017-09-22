//
//  ACRViewController.h
//  ACRViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACRActionDelegate.h"
#import "ACOAdaptiveCard.h"
#import "ACOHostConfig.h"

@interface ACRViewController :UIViewController

@property (weak) id<ACRActionDelegate> acrActionDelegate;

- (instancetype)init:(ACOAdaptiveCard *)card 
          hostconfig:(ACOHostConfig *)config
               frame:(CGRect)frame;

@end
