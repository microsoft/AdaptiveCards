//
//  ACRAggregateTarget
//  ACRAggregateTarget.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRAggregateTarget.h"
#import "ACRContentHoldingUIView.h"
#import "ACRIBaseInputHandler.h"
#import "ACRView.h"

@implementation ACRAggregateTarget
{
    ACOBaseActionElement *_actionElement;
    __weak ACRView *_view;
}

- (instancetype)initWithActionElement:(ACOBaseActionElement *)actionElement rootView:(ACRView*)rootViewController;
{
    self = [super init];
    if(self) {
        _actionElement = actionElement;
        _view = rootViewController;
    }
    return self;
}

- (IBAction)send:(UIButton *)sender
{
    [sender setSelected:YES];
    [_view.acrActionDelegate didFetchUserResponses:[_view card] action:_actionElement];
}

- (void)doSelectAction
{
    [_view.acrActionDelegate didFetchUserResponses:[_view card] action:_actionElement];
}


@end
