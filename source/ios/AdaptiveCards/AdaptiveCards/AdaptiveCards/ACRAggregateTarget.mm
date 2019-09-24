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
        _actionElement = [[ACOBaseActionElement alloc] initWithBaseActionElement:[actionElement element]];
        _view = rootView;
    }
    return self;
}

- (IBAction)send:(UIButton *)sender
{
    [_view.acrActionDelegate didFetchUserResponses:[_view card] action:_actionElement];
}

- (void)doSelectAction
{
    [_view.acrActionDelegate didFetchUserResponses:[_view card] action:_actionElement];
}

@end
