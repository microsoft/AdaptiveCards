//
//  ACRChoiceSetViewDataSourceCompactStyle
//  ACRChoiceSetViewDataSourceCompactStyle.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ChoiceInput.h"
#import "ChoiceSetInput.h"
#import "ACRIBaseInputHandler.h"
#import "HostConfig.h"
#import "ACRViewController.h"

@interface ACRChoiceSetViewDataSourceCompactStyle:NSObject<UITableViewDataSource, UITableViewDelegate, ACRIBaseInputHandler>
@property NSString *id;
@property BOOL isMultiChoicesAllowed;
@property NSMutableDictionary *results;
@property (weak) ACRViewController *vc;

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const&)choiceSet
                        viewController:(UIView *)vc;

- (void)handleUIBarButtonSystemItemDoneEvent;
@end
