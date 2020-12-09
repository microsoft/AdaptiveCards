//
//  ACRAggregateTarget
//  ACRAggregateTarget.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRAggregateTarget.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOInputResults.h"
#import "ACRContentHoldingUIView.h"
#import "ACRIBaseInputHandler.h"
#import "ACRViewController.h"
#import "ACRViewPrivate.h"
#import "SubmitAction.h"
#import <UIKit/UIKit.h>

NSString *const ACRAggregateTargetActionType = @"actiontype";
NSString *const ACRAggregateTargetSubmitAction = @"submit";
NSString *const ACRAggregateTargetFirstResponder = @"firstResponder";

@implementation ACRAggregateTarget {
    BOOL _doValidation;
}

- (instancetype)initWithActionElement:(ACOBaseActionElement *)actionElement rootView:(ACRView *)rootView;
{
    self = [super init];
    if (self) {
        if (actionElement.type == ACRSubmit) {
            auto adaptiveSubmitAction = std::dynamic_pointer_cast<SubmitAction>(actionElement.element);
            _doValidation = adaptiveSubmitAction->GetAssociatedInputs() == AssociatedInputs::Auto;
        }
        _actionElement = actionElement;
        _view = rootView;
        _currentShowcard = [rootView peekCurrentShowCard];
    }
    return self;
}

// main entry point to the event handler, override each methods whithin it for custom behaviors
- (IBAction)send:(UIButton *)sender
{
    if (!_doValidation) {
        [[_view card] setInputs:@[]];
        [_view.acrActionDelegate didFetchUserResponses:[_view card] action:_actionElement];
    }
    // dispatch and validate inputs
    ACOInputResults *result = [_view dispatchAndValidateInput:_currentShowcard];
    // update UI with the inputs
    [self updateInputUI:result button:sender];

    if (result.hasValidationPassed) {
        [self doIfValidationPassed:result button:sender];
    } else {
        [self doIfValidationFailed:result button:sender];
    }
}

- (void)doIfValidationPassed:(ACOInputResults *)results button:(UIButton *)button
{
    if (results) {
        // if a validation passes, gathered input is set in the adaptive card
        [[_view card] setInputs:results.gatheredInputs];
        // dispatch the card to the host app
        [_view.acrActionDelegate didFetchUserResponses:[_view card] action:_actionElement];
    }
}

- (void)doIfValidationFailed:(ACOInputResults *)result button:(UIButton *)button
{
    if (result) {
        // layout changed and notify subscribers

        if ([self.view.acrActionDelegate respondsToSelector:@selector(didChangeViewLayout:newFrame:properties:)]) {
            // focus is set to the first failed input,
            UIView *viewToFocus = (UIView *)result.firstFailedInput;
            // prepare params for notification
            NSDictionary *prop = @{ACRAggregateTargetActionType : ACRAggregateTargetSubmitAction, ACRAggregateTargetFirstResponder : result.firstFailedInput};
            // we want to pass this view to the host app, so the app can compute content offset for scrolling for the focus
            if (viewToFocus) {
                [self.view.acrActionDelegate didChangeViewLayout:CGRectNull newFrame:viewToFocus.frame properties:prop];
            } else {
                [self.view.acrActionDelegate didChangeViewLayout:CGRectNull newFrame:CGRectNull properties:prop];
            }
        } else if ([_view.acrActionDelegate respondsToSelector:@selector(didChangeViewLayout:newFrame:)]) {
            // notify layout change
            [_view.acrActionDelegate didChangeViewLayout:CGRectNull newFrame:CGRectNull];
        }
    }
}

- (void)updateInputUI:(ACOInputResults *)result button:(UIButton *)button
{
    if (result && !result.hasValidationPassed) {
        [result.firstFailedInput setFocus:YES view:nil];
    }
}

- (void)doSelectAction
{
    [_view.acrActionDelegate didFetchUserResponses:[_view card] action:_actionElement];
}

@end
