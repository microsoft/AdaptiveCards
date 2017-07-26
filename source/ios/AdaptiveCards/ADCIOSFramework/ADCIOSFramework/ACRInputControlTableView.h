//
//  ACRInputControlTableViewController
//  ACRInputControlTableViewController.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "ToggleInput.h"
#import "ChoiceInput.h"
#import "ChoiceSetInput.h"
#import "SharedAdaptiveCard.h"
#import "HostConfig.h"

@interface ACRInputControlTableView:UITableView<UITableViewDataSource, UITableViewDelegate>
- (instancetype)initWithInputToggle:(std::shared_ptr<AdaptiveCards::ToggleInput> const&)toggleInput
                     WithHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const&)hostConfig
                      WithSuperview:(UIView *)view;
- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const&)choiceSet
                        WithHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const&)hostConfig
                         WithSuperview:(UIView *)view;
@end
