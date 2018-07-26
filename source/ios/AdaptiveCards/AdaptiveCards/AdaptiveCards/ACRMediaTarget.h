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

@interface ACRMediaTarget:NSObject<ACRSelectActionDelegate>

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent rootView:(ACRView *)rootView config:(ACOHostConfig *)config;

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent
                          rootView:(ACRView *)rootView
                            config:(ACOHostConfig *)config
                    containingview:(UIView *)containingview
                         superview:(UIView<ACRIContentHoldingView> *)superview;
- (void)doSelectAction;

- (void)getNaturalSize:(AVAssetTrack *)track asset:(AVURLAsset *)asset;

- (void)getAVTrack:(AVURLAsset *)asset;

@end
