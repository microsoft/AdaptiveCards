//
//  ACRQuickReplyView
//  ACRQuickReplyView.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRAggregateTarget.h"
#import "ACRButton.h"
#import "ACRTextField.h"
#import "ACRQuickReplyMultilineView.h"
#import <UIKit/UIKit.h>

@interface ACRQuickReplyView : UIView <UITextFieldDelegate, ACRIQuickReply>
@property (strong, nonatomic) IBOutlet UIView *contentView;
@property (weak, nonatomic) IBOutlet ACRTextField *textFileld;
@property (weak, nonatomic) IBOutlet UIView *spacing;
@property (weak, nonatomic) IBOutlet ACRButton *button;
@property (weak, nonatomic) ACRAggregateTarget *target;
@end
