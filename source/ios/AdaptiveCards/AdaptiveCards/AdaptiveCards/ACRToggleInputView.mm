//
//  ACRToggleInputView.m
//  AdaptiveCards
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACRToggleInputView.h"
#import <Foundation/Foundation.h>

@implementation ACRToggleInputView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self commonInit];
    }
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)coder
{
    self = [super initWithCoder:coder];
    if (self) {
        [self commonInit];
    }

    return self;
}

- (void)commonInit
{
    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    // nib can have more than one view serialized
    _contentview = [bundle loadNibNamed:@"ACRToggleInputView" owner:self options:nil][0];

    self.translatesAutoresizingMaskIntoConstraints = NO;

    _contentview.translatesAutoresizingMaskIntoConstraints = NO;

    [self addSubview:_contentview];

    [_contentview.leadingAnchor constraintEqualToAnchor:self.layoutMarginsGuide.leadingAnchor].active = YES;
    [_contentview.trailingAnchor constraintEqualToAnchor:self.layoutMarginsGuide.trailingAnchor].active = YES;
    [_contentview.centerYAnchor constraintEqualToAnchor:self.layoutMarginsGuide.centerYAnchor].active = YES;
    [_contentview.heightAnchor constraintEqualToAnchor:self.heightAnchor].active = YES;
    [_title setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
     // we configure the margin to nil, and have users of SDK configure margins through xib interface's container view
    if (@available(iOS 11.0, *)) {
        NSDirectionalEdgeInsets insets = self.directionalLayoutMargins;
        insets.leading = 0.0f;
        insets.trailing = 2.0f;
        self.directionalLayoutMargins = insets;
    } else {
        UIEdgeInsets insets = self.layoutMargins;
        insets.left = 0.0f;
        insets.right = 2.0f;
        self.layoutMargins = insets;
    }
}

- (CGSize)intrinsicContentSize
{
    CGSize labelIntrinsicContentSize = [_title intrinsicContentSize];
    CGSize switchIntrinsicContentSize = [_toggle intrinsicContentSize];
    return CGSizeMake(labelIntrinsicContentSize.width + _contentview.spacing + switchIntrinsicContentSize.width, MAX(labelIntrinsicContentSize.height, switchIntrinsicContentSize.height));
}
@end
