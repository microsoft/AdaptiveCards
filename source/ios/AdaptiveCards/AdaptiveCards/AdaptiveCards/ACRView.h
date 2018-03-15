//
//  ACRView.h
//  ACRView
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACRActionDelegate.h"
#import "ACOAdaptiveCard.h"
#import "ACOHostConfig.h"

@interface ACRView:UIView

@property (weak) id<ACRActionDelegate>acrActionDelegate;

- (instancetype)init:(ACOAdaptiveCard *)card hostconfig:(ACOHostConfig *)config frame:(CGRect)frame;

- (NSMutableDictionary *)getImageMap;

- (dispatch_queue_t)getSerialQueue;

- (NSMutableDictionary *)getTextMap;

- (dispatch_queue_t)getSerialTextQueue;

- (ACOAdaptiveCard *)card;
@end
