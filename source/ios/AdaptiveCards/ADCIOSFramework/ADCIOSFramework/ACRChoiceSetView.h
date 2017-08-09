//
//  ACRChoiceSetView
//  ACRChoiceSetView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputControlTableView.h"
#import "ChoiceInput.h"
#import "ChoiceSetInput.h"

@interface ACRChoiceSetView:ACRInputControlTableView
- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const&)choiceSet
                            hostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const&)hostConfig
                             superview:(UIView *)view;
@end
