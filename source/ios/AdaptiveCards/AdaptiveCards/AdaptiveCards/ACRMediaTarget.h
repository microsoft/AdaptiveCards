//
//  ACRMeidaTarget
//  ACRMeidaTarget.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "ACRView.h"
#import "ACOMediaEvent.h"
#import "ACRLongPressGestureRecognizerEventHandler.h"

extern const int playIconTag;
extern const int posterTag;

@interface ACRMediaTarget:NSObject<ACRSelectActionDelegate>

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent rootView:(ACRView *)rootView config:(ACOHostConfig *)config;

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent
                          rootView:(ACRView *)rootView
                            config:(ACOHostConfig *)config
                    containingview:(UIView *)containingview;
- (void)doSelectAction;

- (void)playMedia:(AVAssetTrack *)track asset:(AVURLAsset *)asset;

- (void)playVideoWhenTrackIsReady:(AVURLAsset *)asset;

@end
