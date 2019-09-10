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
    [self addSubview:self.contentView];
    self.contentView.frame = self.bounds;
    self.contentView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    if (_target) {
        [_target send:self.button];
    }
    [self resignFirstResponder];
    [self endEditing:YES];
    return YES;
}

- (void)dismissNumPad
{
    [self resignFirstResponder];
}
@end
