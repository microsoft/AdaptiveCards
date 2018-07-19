//
//  ACRMeidaTarget
//  ACRMeidaTarget.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRView.h"
#import "ACOMediaEvent.h"
#import "ACRLongPressGestureRecognizerEventHandler.h"

@interface ACRMediaTarget:NSObject<ACRSelectActionDelegate>

- (instancetype)initWithMediaEvent:(ACOMediaEvent *)mediaEvent rootView:(ACRView *)rootView config:(ACOHostConfig *)config;

- (instancetype)initWithMediaViewController:(AVPlayerViewController *)mediaViewController
                                   rootView:(ACRView *)rootView
                                     config:(ACOHostConfig *)config
                                     poster:(UIView *)poster
                                  superview:(UIView<ACRIContentHoldingView> *)superview;
- (void)doSelectAction;

@end
