//
//  ACRQuickReplyMultilineView
//  ACRQuickReplyMultilineView.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRButton.h"
#import "ACRTextView.h"
#import <UIKit/UIKit.h>
@protocol ACRIQuickReply
- (ACRButton *)getButton;
@end

@interface ACRQuickReplyMultilineView : UIView <ACRIQuickReply>
@property (strong, nonatomic) IBOutlet UIView *contentView;
@property (weak, nonatomic) IBOutlet ACRTextView *textView;
@property (weak, nonatomic) IBOutlet UIView *spacing;
@property (weak, nonatomic) IBOutlet ACRButton *button;

@end
