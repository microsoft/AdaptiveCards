//
//  ACRAggregateTarget
//  ACRAggregateTarget.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRIContentHoldingView.h"
#import "ACRLongPressGestureRecognizerEventHandler.h"
#import "ACOInputResults.h"
#import "ACRView.h"
#import <UIKit/UIKit.h>

// AggregateTraget is used to relay the signal back to host
@interface ACRAggregateTarget : NSObject <ACRSelectActionDelegate>
@property ACOBaseActionElement *actionElement;
@property (weak) ACRView *view;
@property (weak) ACRColumnView *currentShowcard;

- (instancetype)initWithActionElement:(ACOBaseActionElement *)actionElement rootView:(ACRView *)rootView;

- (IBAction)send:(UIButton *)sender;

- (void)doIfValidationPassed:(ACOInputResults *)results button:(UIButton *)button;

- (void)doIfValidationFailed:(ACOInputResults *)results button:(UIButton *)button;

- (void)doSelectAction;

@end
