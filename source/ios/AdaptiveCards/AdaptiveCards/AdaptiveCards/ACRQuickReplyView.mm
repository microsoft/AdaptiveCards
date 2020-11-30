//
//  ACRQuickReplyView
//  ACRQuickReplyView.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRQuickReplyView.h"


@implementation ACRQuickReplyView


- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    [self commonInit];
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    [self commonInit];
    return self;
}

- (void)commonInit
{
    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    [bundle loadNibNamed:@"ACRQuickActionView" owner:self options:nil];
    [self addSubview:self.stack];
    self.layoutMargins = UIEdgeInsetsMake(0, 0, 0, 0);
    self.translatesAutoresizingMaskIntoConstraints = NO;
    [self.layoutMarginsGuide.leadingAnchor constraintEqualToAnchor:self.stack.leadingAnchor].active = YES;
    [self.layoutMarginsGuide.trailingAnchor constraintEqualToAnchor:self.stack.trailingAnchor].active = YES;
    [self.layoutMarginsGuide.topAnchor constraintEqualToAnchor:self.stack.topAnchor].active = YES;
    [self.layoutMarginsGuide.bottomAnchor constraintEqualToAnchor:self.stack.bottomAnchor].active = YES;
}

- (void) addTextField:(ACRTextField *)textField
{
    [self.stack insertArrangedSubview:textField atIndex:0];
    [textField setContentHuggingPriority:249 forAxis:UILayoutConstraintAxisHorizontal];
    [textField setContentCompressionResistancePriority:749 forAxis:UILayoutConstraintAxisHorizontal];
    self.textField = textField;
}

- (BOOL)becomeFirstResponder {
    if (self.textField) {
        [self.textField becomeFirstResponder];
    }
    return YES;
}

- (BOOL)resignFirstResponder {
    if (self) {
        [self.textField resignFirstResponder];
    }
    return YES;
}

- (void)dismissNumPad
{
    [self resignFirstResponder];
}

- (ACRButton *)getButton
{
    return _button;
}
@end
