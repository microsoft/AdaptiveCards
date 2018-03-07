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

@interface ACRViewController :UIView

@property (weak) id<ACRActionDelegate> acrActionDelegate;
@property (readonly, weak) UIViewController *rootViewController;

- (instancetype)init:(ACOAdaptiveCard *)card 
          hostconfig:(ACOHostConfig *)config
               frame:(CGRect)frame
  rootViewController:(UIViewController *)rootViewController;

- (NSMutableDictionary *) getImageMap;

- (dispatch_queue_t) getSerialQueue;

- (NSMutableDictionary *) getTextMap; 

- (dispatch_queue_t) getSerialTextQueue;

- (ACOAdaptiveCard *) card;
@end
