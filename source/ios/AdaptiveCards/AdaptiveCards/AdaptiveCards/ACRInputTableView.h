//
//  ACRInputTableView
//  ACRInputTableView.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRIBaseInputHandler.h"
#else
#import <AdaptiveCards/ACRIBaseInputHandler.h>
#endif
#import <UIKit/UIKit.h>

@interface ACRInputTableView : UITableView

@property IBInspectable CGFloat inputTableViewSpacing;

- (instancetype)initWithSuperview:(UIView *)view;

@end
