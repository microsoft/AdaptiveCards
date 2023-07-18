//
//  ACRAggregateTarget
//  ACRAggregateTarget.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACOInputResults.h"
#import "ACRBaseTarget.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACOInputResults.h>
#import <AdaptiveCards/ACRBaseTarget.h>
#endif
#import "ACRIContentHoldingView.h"
#import "ACRView.h"
#import <UIKit/UIKit.h>

// keys used in retrieving values from properties that are dispatced by
// didChangeViewLayout: newFrame: properties:
// possible values contained in the properties
// a key that retreives an ActionType
extern NSString *const ACRAggregateTargetActionType;
// a possible value of ActionType key, SubmitAction
extern NSString *const ACRAggregateTargetSubmitAction;
// a key that retreives a view that is a FirstResponder in AdaptiveCards as a result of a submit action on the card
extern NSString *const ACRAggregateTargetFirstResponder;

// AggregateTraget is used to relay the signal back to host
// It's associated with Action.Submit
@interface ACRAggregateTarget : ACRBaseTarget
@property ACOBaseActionElement *actionElement;
@property (weak) ACRView *view;
@property (weak) ACRColumnView *currentShowcard;

- (instancetype)initWithActionElement:(ACOBaseActionElement *)actionElement rootView:(ACRView *)rootView;

// It's the event handler when the button referenced by sender is activated
- (IBAction)send:(UIButton *)sender;
// it's the method called when input validation succeed
- (void)doIfValidationPassed:(ACOInputResults *)results button:(UIButton *)button;
// it's the method called when input validation failed
- (void)doIfValidationFailed:(ACOInputResults *)results button:(UIButton *)button;
// it's called after input gathering is done, and does UI updates for inputs UI
- (void)updateInputUI:(ACOInputResults *)result button:(UIButton *)button;

- (void)doSelectAction;

@end
