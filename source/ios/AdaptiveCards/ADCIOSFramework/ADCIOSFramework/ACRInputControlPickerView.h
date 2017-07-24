//
//  ACRInputControlPickerViewController
//  ACRInputControlPickerViewController.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "ChoiceSetInput.h"
#import "SharedAdaptiveCard.h"
#import "HostConfig.h"

@interface ACRInputControlPickerView:UIPickerView<UIPickerViewDataSource, UIPickerViewDelegate>
- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const&)choiceSet
                        WithHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig>     const&)hostConfig
                         WithSuperview:(UIView* )view;
@end
