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

@interface ACRQuickReplyView : UIView <ACRIQuickReply>
@property (strong, nonatomic) IBOutlet UIStackView *stack;
@property ACRTextField *textField;
@property (weak, nonatomic) IBOutlet ACRButton *button;
@property (weak, nonatomic) ACRAggregateTarget *target;
- (void) addTextField:(ACRTextField *)textField;
@end
