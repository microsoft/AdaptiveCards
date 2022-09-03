//
//  ACRQuickReplyView
//  ACRQuickReplyView.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRAggregateTarget.h"
#import "ACRButton.h"
#import "ACRQuickReplyMultilineView.h"
#import "ACRTextField.h"
#else
#import <AdaptiveCards/ACRAggregateTarget.h>
#import <AdaptiveCards/ACRButton.h>
#import <AdaptiveCards/ACRQuickReplyMultilineView.h>
#import <AdaptiveCards/ACRTextField.h>
#endif
#import <UIKit/UIKit.h>

@interface ACRQuickReplyView : UIView <ACRIQuickReply>
@property (strong, nonatomic) IBOutlet UIStackView *stack;
@property ACRTextField *textField;
@property (weak, nonatomic) IBOutlet ACRButton *button;
@property (weak, nonatomic) ACRAggregateTarget *target;
- (void)addTextField:(ACRTextField *)textField;
@end
