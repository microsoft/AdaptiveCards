//
//  ACRAggregateTarget
//  ACRAggregateTarget.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRIContentHoldingView.h"
#import "ACRLongPressGestureRecognizerEventHandler.h"
#import "ACRView.h"
#import <UIKit/UIKit.h>

// AggregateTraget is used to relay the signal back to host
@interface ACRAggregateTarget : NSObject <ACRSelectActionDelegate>

- (instancetype)initWithActionElement:(ACOBaseActionElement *)actionElement rootView:(ACRView *)rootView;

- (IBAction)send:(UIButton *)sender;

- (void)doSelectAction;

@end
