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
#import "ACRColumnView.h"
#import "ACRIMedia.h"

@interface ACRView:ACRColumnView

@property (weak) id<ACRActionDelegate>acrActionDelegate;
@property (weak) id<ACRMediaDelegate>mediaDelegate;

- (instancetype)init:(ACOAdaptiveCard *)card hostconfig:(ACOHostConfig *)config widthConstraint:(float)width;

- (NSMutableDictionary *)getImageMap;

- (dispatch_queue_t)getSerialQueue;

- (NSMutableDictionary *)getTextMap;

- (ACOAdaptiveCard *)card;

- (UIView *)render;

- (void)waitForAsyncTasksToFinish;
@end
