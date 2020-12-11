//
//  ACRInputTableView
//  ACRInputTableView.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRIBaseInputHandler.h"
#import "ChoiceInput.h"
#import "ChoiceSetInput.h"
#import "HostConfig.h"
#import <UIKit/UIKit.h>

@interface ACRInputTableView : UITableView

@property IBInspectable CGFloat inputTableViewSpacing;

- (instancetype)initWithSuperview:(UIView *)view;

@end
