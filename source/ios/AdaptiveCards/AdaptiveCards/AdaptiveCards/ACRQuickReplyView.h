//
//  ACRQuickReplyView
//  ACRQuickReplyView.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRTextField.h"
#import "ACRButton.h"

@interface ACRQuickReplyView:UIView
@property (strong, nonatomic) IBOutlet UIView *contentView;
@property (weak, nonatomic) IBOutlet ACRTextField *textFileld;
@property (weak, nonatomic) IBOutlet UIView *spacing;
@property (weak, nonatomic) IBOutlet UIButton *button;

@end
