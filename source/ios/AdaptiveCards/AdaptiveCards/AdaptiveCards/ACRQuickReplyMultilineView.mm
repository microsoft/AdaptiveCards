//
//  ACRQuickReplyMultilineView
//  ACRQuickReplyMultilineView.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRQuickReplyMultilineView.h"


@implementation ACRQuickReplyMultilineView


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
    [SWIFTPM_MODULE_BUNDLE loadNibNamed:@"ACRQuickActionMultilineView" owner:self options:nil];
    [self addSubview:self.contentView];
    self.contentView.frame = self.bounds;
    self.contentView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
}

- (ACRButton *)getButton
{
    return _button;
}

@end
