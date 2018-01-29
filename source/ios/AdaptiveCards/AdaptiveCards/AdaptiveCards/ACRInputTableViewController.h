//
//  ACRInputTableViewController
//  ACRInputTableViewController.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

//#import "ACRInputControlTableView.h"
//#import "ChoiceInput.h"
#import "ChoiceSetInput.h"
#import <UIKit/UIKit.h>

@interface ACRInputTableViewController:UITableViewController
- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const&)choiceSet
                            //hostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const&)hostConfig
                                 style:(UITableViewStyle)style;


@end
