//
//  ACRChoiceSetView
//  ACRChoiceSetView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ChoiceInput.h"
#import "ChoiceSetInput.h"
#import "ACRIBaseInputHandler.h"
#import "HostConfig.h"

@interface ACRChoiceSetView:UITableView<UITableViewDataSource, UITableViewDelegate, ACRIBaseInputHandler> 
@property NSString *id;
@property BOOL isSelected;
@property NSMutableDictionary *results;
@property (weak) UIViewController *vc;

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const&)choiceSet
                            hostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const&)hostConfig
                             superview:(UIView *)view;

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const&)choiceSet
                            hostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const&)hostConfig
                             superview:(UIView *)view
                        viewController:(UIViewController *)vc;

- (void)handleUIBarButtonSystemItemDoneEvent;
@end
