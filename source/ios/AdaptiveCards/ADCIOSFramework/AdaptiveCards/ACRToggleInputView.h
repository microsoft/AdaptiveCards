//
//  ACRToggleInputView
//  ACRToggleInputView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputControlTableView.h"
#import "ToggleInput.h"
#import "ACRIBaseInputHandler.h"

@interface ACRToggleInputView:ACRInputControlTableView

- (instancetype)initWithInputToggle:(std::shared_ptr<AdaptiveCards::ToggleInput> const&)toggleInput
                     WithHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const&)hostConfig
                      WithSuperview:(UIView *)view;
@end
