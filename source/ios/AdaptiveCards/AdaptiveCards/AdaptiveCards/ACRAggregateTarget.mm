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
#import <UIKit/UIKit.h>

@implementation ACRAggregateTarget

- (instancetype)initWithActionElement:(ACOBaseActionElement *)actionElement rootView:(ACRView *)rootView;
{
    self = [super init];
    if (self) {
        _actionElement = actionElement;
        _view = rootView;
        _currentShowcard = [rootView peekCurrentShowCard];
    }
    return self;
}

- (IBAction)send:(UIButton *)sender
{
    ACOInputResults *result = [_view dispatchAndValidateInput:_currentShowcard];

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
        [[_view card] setInputs:results.gatheredInputs];
        [_view.acrActionDelegate didFetchUserResponses:[_view card] action:_actionElement];
    }
}

- (void)doIfValidationFailed:(ACOInputResults *)result button:(UIButton *)button
{
    if (result) {
        if (result.hasViewChangedForAnyViews && [_view.acrActionDelegate respondsToSelector:@selector(didChangeViewLayout:newFrame:)]) {
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
