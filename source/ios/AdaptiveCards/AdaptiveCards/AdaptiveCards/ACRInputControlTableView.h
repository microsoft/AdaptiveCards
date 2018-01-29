//
//  ACRInputControlTable
//  ACRInputControlTable.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "SharedAdaptiveCard.h"
#import "HostConfig.h"
#import "ACRIBaseInputHandler.h"

@interface ACRInputControlTableView:UITableView<UITableViewDataSource, UITableViewDelegate, ACRIBaseInputHandler>

@property NSString *id;
@property NSString *valueOn;
@property NSString *valueOff;
@property BOOL isSelected;
@property NSMutableDictionary *results;
@property (weak) UIViewController *vc;

- (instancetype)initWithFrame:(CGRect)frame
                        style:(UITableViewStyle)style viewController:(UIViewController *)vc;

- (void)handleUIBarButtonSystemItemDoneEvent;

@end
