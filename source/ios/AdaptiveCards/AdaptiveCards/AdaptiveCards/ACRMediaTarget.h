//
//  ACRMeidaTarget
//  ACRMeidaTarget.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOMediaEvent.h"
#import "ACRLongPressGestureRecognizerEventHandler.h"
#import "ACRView.h"
#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>

extern const int playIconTag;
extern const int posterTag;

@interface ACRMediaTarget : NSObject <ACRSelectActionDelegate>

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent rootView:(ACRView *)rootView config:(ACOHostConfig *)config;

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent
                          rootView:(ACRView *)rootView
                            config:(ACOHostConfig *)config
                    containingview:(UIView *)containingview;
- (void)doSelectAction;

- (void)playMedia:(AVAssetTrack *)track asset:(AVURLAsset *)asset;

- (void)playVideoWhenTrackIsReady:(AVURLAsset *)asset;

@end
