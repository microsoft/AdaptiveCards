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
    __weak ACRView *_vc;
}

- (instancetype)initWithActionElement:(ACOBaseActionElement *)actionElement rootView:(ACRView*)rootViewController;
{
    self = [super init];
    if(self) {
        _actionElement = actionElement;
        _vc = rootViewController;
    }
    return self;
}

- (IBAction)send:(UIButton *)sender
{
    [sender setSelected:YES];
    [_vc.acrActionDelegate didFetchUserResponses:[_vc card] action:_actionElement];
}

- (void)doSelectAction
{
    [_vc.acrActionDelegate didFetchUserResponses:[_vc card] action:_actionElement];
}


@end
