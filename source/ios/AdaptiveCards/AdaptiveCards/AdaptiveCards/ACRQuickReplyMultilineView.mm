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
    NSBundle* bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    [bundle loadNibNamed:@"ACRQuickActionMultilineView" owner:self options:nil];
    [self addSubview:self.contentView];
    self.contentView.frame = self.bounds;
    self.contentView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
}

- (CGSize)intrinsicContentSize
{
    return CGSizeMake(self.textView.frame.size.width + self.button.frame.size.width + 30 + 32, self.textView.frame.size.height + self.button.frame.size.height + 30 + 32);
}
@end
