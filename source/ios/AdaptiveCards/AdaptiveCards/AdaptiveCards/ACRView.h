//
//  ACRView.h
//  ACRView
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOAdaptiveCard.h"
#import "ACOHostConfig.h"
#import "ACOWarning.h"
#import "ACRActionDelegate.h"
#import "ACRColumnView.h"
#import "ACRIMedia.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ACRView : ACRColumnView

@property (weak) id<ACRActionDelegate> acrActionDelegate;
@property (weak) id<ACRMediaDelegate> mediaDelegate;
@property NSArray<ACOWarning *> *warnings;

- (instancetype)init:(ACOAdaptiveCard *)card hostconfig:(ACOHostConfig *)config widthConstraint:(float)width;
- (instancetype)init:(ACOAdaptiveCard *)card
          hostconfig:(ACOHostConfig *)config
     widthConstraint:(float)width
            delegate:(id<ACRActionDelegate>)acrActionDelegate;

- (NSMutableDictionary *)getImageMap;

- (UIImageView *)getImageView:(NSString *)key;

- (void)setImageView:(NSString *)key view:(UIView *)view;

- (dispatch_queue_t)getSerialQueue;

- (NSMutableDictionary *)getTextMap;

- (ACOAdaptiveCard *)card;

- (UIView *)render;

- (void)waitForAsyncTasksToFinish;

@end
