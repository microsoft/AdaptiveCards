//
//  ACRToggleVisibilityTarget
//  ACRToggleVisibilityTarget.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRToggleVisibilityTarget.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACOVisibilityManager.h"
#import "ACRRendererPrivate.h"
#import "ACRView.h"
#import "BaseActionElement.h"
#import "ToggleVisibilityTarget.h"

@implementation ACRToggleVisibilityTarget {
    ACOHostConfig *_config;
    __weak ACRView *_rootView;
    std::shared_ptr<ToggleVisibilityAction> _action;
}

- (instancetype)initWithActionElement:(std::shared_ptr<AdaptiveCards::ToggleVisibilityAction> const &)actionElement
                               config:(ACOHostConfig *)config
                             rootView:(ACRView *)rootView
{
    self = [super init];
    if (self) {
        _config = config;
        _rootView = rootView;
        _action = std::make_shared<ToggleVisibilityAction>(*(actionElement.get()));
    }
    return self;
}

- (void)doSelectAction
{
    NSMutableSet<id<ACOIVisibilityManagerFacade>> *facades = [[NSMutableSet alloc] init];
    for (const auto &target : _action->GetTargetElements()) {
        NSString *hashString = [NSString stringWithCString:target->GetElementId().c_str() encoding:NSUTF8StringEncoding];
        NSUInteger tag = hashString.hash;
        UIView *view = [_rootView viewWithTag:tag];
        BOOL bHide = NO;

        id<ACOIVisibilityManagerFacade> facade = [_rootView.context retrieveVisiblityManagerWithTag:view.tag];
        [facades addObject:facade];

        AdaptiveCards::IsVisible toggleEnum = target->GetIsVisible();
        if (toggleEnum == AdaptiveCards::IsVisibleToggle) {
            BOOL isHidden = view.isHidden;
            bHide = !isHidden;
        } else if (toggleEnum == AdaptiveCards::IsVisibleTrue) {
            bHide = NO;
        } else {
            bHide = YES;
        }

        if (facade) {
            if (bHide) {
                [facade hideView:view];
            } else {
                [facade unhideView:view];
            }
        }
    }

    for (id<ACOIVisibilityManagerFacade> viewToUpdateVisibility in facades) {
        [viewToUpdateVisibility updatePaddingVisibility];
    }

    [_rootView.acrActionDelegate didFetchUserResponses:[_rootView card] action:[[ACOBaseActionElement alloc] initWithBaseActionElement:_action]];
}

@end
