//
//  ACRAggregateTarget
//  ACRAggregateTarget.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRIContentHoldingView.h"
#import "ACRLongPressGestureRecognizerEventHandler.h"
#import "ACRView.h"
#import "HostConfig.h"
#import "SharedAdaptiveCard.h"
#import <UIKit/UIKit.h>

@interface ACRAggregateTarget : NSObject <ACRSelectActionDelegate>

- (instancetype)initWithActionElement:(ACOBaseActionElement *)actionElement rootView:(ACRView *)rootView;

- (IBAction)send:(UIButton *)sender;

- (void)doSelectAction;

@end
