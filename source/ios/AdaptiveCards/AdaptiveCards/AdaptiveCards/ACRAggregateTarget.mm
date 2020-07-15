//
//  ACRAggregateTarget
//  ACRAggregateTarget.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRAggregateTarget.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACRIBaseInputHandler.h"
#import "ACRView.h"
#import "ACRViewController.h"
#import <UIKit/UIKit.h>

@implementation ACRAggregateTarget {
    ACOBaseActionElement *_actionElement;
    __weak ACRView *_view;
}

- (instancetype)initWithActionElement:(ACOBaseActionElement *)actionElement rootView:(ACRView *)rootView;
{
    self = [super init];
    if (self) {
        _actionElement = actionElement;
        _view = rootView;
    }
    return self;
}

- (IBAction)send:(UIButton *)sender
{
    ACOAdaptiveCard *acoCard = [_view card];
    NSArray<ACRIBaseInputHandler> *inputs = [acoCard getInputs];
    BOOL hasValidationPassed = YES;
    NSError *error = nil;
    for (id<ACRIBaseInputHandler> input in inputs)
    {
        hasValidationPassed &= [input validate:&error];
    }
    
    if (hasValidationPassed) {
        [_view.acrActionDelegate didFetchUserResponses:[_view card] action:_actionElement];
    }
}

- (void)doSelectAction
{
    [_view.acrActionDelegate didFetchUserResponses:[_view card] action:_actionElement];
}

@end
