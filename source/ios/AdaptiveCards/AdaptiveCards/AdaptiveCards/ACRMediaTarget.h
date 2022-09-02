//
//  ACRMeidaTarget
//  ACRMeidaTarget.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACOMediaEvent.h>
#import <AdaptiveCards/ACRTapGestureRecognizerEventHandler.h>
#import <AdaptiveCards/ACRView.h>
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
