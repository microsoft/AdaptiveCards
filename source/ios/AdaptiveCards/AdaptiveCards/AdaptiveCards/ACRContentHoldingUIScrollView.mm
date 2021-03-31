//
//  ACRContentHoldingUIScrollView
//  ACRContentHoldingUIScrollView.mm
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACRContentHoldingUIScrollView.h"

@implementation ACRContentHoldingUIScrollView

- (CGSize)intrinsicContentSize
{
    // whenever intrinsic content size is called, re-check if content size for subviews have changed
    if (self.contentview) {
        CGFloat maxWidth = 0.0f, maxHeight = 0.0f, accumulatedWidth = 0.0f, accumulatedHeight = 0.0f;
        for (UIView *subview in self.contentview.arrangedSubviews) {
            CGSize size = [subview intrinsicContentSize];
            accumulatedWidth += size.width;
            accumulatedHeight += size.height;
            maxWidth = MAX(maxWidth, size.width);
            maxHeight = MAX(maxHeight, size.height);
        }

        NSUInteger count = [self.contentview.arrangedSubviews count];
        CGFloat spacing = count == 0 ? 0 : self.spacing * (count - 1);

        return (self.contentview.axis == UILayoutConstraintAxisHorizontal) ? CGSizeMake(accumulatedWidth + spacing, maxHeight) : CGSizeMake(maxWidth, accumulatedHeight + spacing);
    }

    return CGSizeMake(-1, -1);
}

- (void)layoutSubviews
{
    self.contentWidth = [self intrinsicContentSize].width;

    // if content size is smaller than the superview, and stretch is specified, stretch content view
    if (self.contentview && (self.stretch && self.frame.size.width > self.contentWidth && !self.widthConstraintForStretch.active)) {
        // add new constraints before layoutSubview before layout pass
        self.widthConstraintForStretch = [self.contentview.widthAnchor constraintEqualToAnchor:self.widthAnchor multiplier:1.0];
        self.widthConstraintForStretch.active = YES;

        self.centerXConstraintForStretch = [self.contentview.centerXAnchor constraintEqualToAnchor:self.centerXAnchor];
        self.centerXConstraintForStretch.active = YES;

        self.centerYConstraintForStretch = [self.contentview.centerYAnchor constraintEqualToAnchor:self.centerYAnchor];
        self.centerYConstraintForStretch.active = YES;

        // layout pass
        [super layoutSubviews];
        // everything is done
        return;
    }

    // if contentWidth is bigger than superview's frame width and content size contraints have been never set
    // then execute if statements
    if (self.frame.size.width < self.contentWidth && !_isContentSizeConstraintSet) {
        _isContentSizeConstraintSet = YES;
        // de-activate constraints
        if (self.widthConstraintForStretch) {
            self.widthConstraintForStretch.active = NO;
        }

        if (self.centerXConstraintForStretch) {
            self.centerXConstraintForStretch.active = NO;
        }

        if (self.centerYConstraintForStretch) {
            self.centerYConstraintForStretch.active = NO;
        }

        // following constraints enables scrolling behaviors
        [NSLayoutConstraint constraintWithItem:self
                                     attribute:NSLayoutAttributeTop
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:self.contentview
                                     attribute:NSLayoutAttributeTop
                                    multiplier:1.0
                                      constant:0]
            .active = YES;
        [NSLayoutConstraint constraintWithItem:self
                                     attribute:NSLayoutAttributeBottom
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:self.contentview
                                     attribute:NSLayoutAttributeBottom
                                    multiplier:1.0
                                      constant:0]
            .active = YES;
        [NSLayoutConstraint constraintWithItem:self
                                     attribute:NSLayoutAttributeLeading
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:self.contentview
                                     attribute:NSLayoutAttributeLeading
                                    multiplier:1.0
                                      constant:0]
            .active = YES;
        [NSLayoutConstraint constraintWithItem:self
                                     attribute:NSLayoutAttributeTrailing
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:self.contentview
                                     attribute:NSLayoutAttributeTrailing
                                    multiplier:1.0
                                      constant:0]
            .active = YES;


        // now ready for layout pass
        [super layoutSubviews];
    }
}

@end
