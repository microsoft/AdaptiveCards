//
//  ACRToggleVisibilityTarget
//  ACRToggleVisibilityTarget.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRToggleVisibilityTarget.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOHostConfigPrivate.h"
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

        NSMutableString *hashStringForSeparator = [NSMutableString stringWithCString:target->GetElementId().c_str() encoding:NSUTF8StringEncoding];
        [hashStringForSeparator appendString:@"-separator"];
        NSUInteger separatorTag = hashStringForSeparator.hash;
        UIView *separator = [_rootView viewWithTag:separatorTag];

        AdaptiveCards::IsVisible toggleEnum = target->GetIsVisible();
        if (toggleEnum == AdaptiveCards::IsVisibleToggle) {
            view.hidden = !(view.hidden);
            if (separator) {
                separator.hidden = view.hidden;
            }
        } else if (toggleEnum == AdaptiveCards::IsVisibleTrue) {
            if (view.hidden == YES) {
                view.hidden = NO;
            }
            if (separator && separator.hidden == YES) {
                separator.hidden = NO;
            }
        } else {
            if (view.hidden == NO) {
                view.hidden = YES;
            }
            if (separator && separator.hidden == NO) {
                separator.hidden = YES;
            }
        }
    }

    [_rootView.acrActionDelegate didFetchUserResponses:[_rootView card] action:[[ACOBaseActionElement alloc] initWithBaseActionElement:_action]];
}

@end
