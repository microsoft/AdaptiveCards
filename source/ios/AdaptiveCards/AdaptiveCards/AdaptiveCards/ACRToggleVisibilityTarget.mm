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
    for (const auto &target : _action->GetTargetElements()) {
        NSString *hashString = [NSString stringWithCString:target->GetElementId().c_str() encoding:NSUTF8StringEncoding];
        NSUInteger tag = hashString.hash;
        UIView *view = [_rootView viewWithTag:tag];
        UIView *separator = nil;
        BOOL bHide = NO;

        id<ACOIVisibilityManagerFacade> facade = [_rootView.context retrieveVisiblityManagerWithTag:view.tag];
        // if facade is available, use the interface, otherwise stick to the old interface until the change is complete
        if (!facade) {
            NSMutableString *hashStringForSeparator = [NSMutableString stringWithCString:target->GetElementId().c_str() encoding:NSUTF8StringEncoding];
            [hashStringForSeparator appendString:@"-separator"];
            NSUInteger separatorTag = hashStringForSeparator.hash;
            separator = [_rootView viewWithTag:separatorTag];
        }

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
        } else {
            if (bHide) {
                if (!view.isHidden) {
                    view.hidden = bHide;
                }
                if (separator && !separator.isHidden) {
                    separator.hidden = bHide;
                }
            } else {
                if (view.isHidden) {
                    view.hidden = bHide;
                }
                if (separator && separator.isHidden) {
                    separator.hidden = bHide;
                }
            }
        }
    }

    [_rootView.acrActionDelegate didFetchUserResponses:[_rootView card] action:[[ACOBaseActionElement alloc] initWithBaseActionElement:_action]];
}

@end
