//
//  ACRUILabel.m
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRUILabel.h"
#import "ACRContentHoldingUIView.h"

@implementation ACRUILabel

-(instancetype)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if(self) {
        self.tag = eACRUILabelTag;
    }
    return self;
}

-(instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if(self) {
        self.tag = eACRUILabelTag;
    }
    return self;
}

/*
- (CGSize)intrinsicContentSize
{
    CGSize intrinsicContentSize = self.contentSize;
    intrinsicContentSize.width += (self.textContainerInset.left + self.textContainerInset.right ) / 2.0f;
    intrinsicContentSize.height += (self.textContainerInset.top + self.textContainerInset.bottom) / 2.0f;
    
    return intrinsicContentSize;
}
 */

- (void)layoutSubviews
{
    [super layoutSubviews];

   if (self.tag == eACRUILabelTag) {
       //CGSize size = [self sizeThatFits:self.superview.frame.size];
       //if (!CGSizeEqualToSize(size, [self intrinsicContentSize])) {
       //    _heightconst.constant = size.height;
       //}
       
        //NSLayoutConstraint *heightconst =
        //[NSLayoutConstraint constraintWithItem:self attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:self.contentSize.height];
        //heightconst.active = YES;
       //CGSize size = [self sizeThatFits:CGSizeMake(self.superview.frame.size.width, self.contentSize.height)];
       //self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, size.width, size.height);
       //[self sizeToFit];
    } else  if (self.tag == eACRUIFactSetTag) {
        CGFloat area = self.frame.size.height * self.frame.size.width;
        if (area != _area) {
            [self invalidateIntrinsicContentSize];
            _area = area;
        }
    }
}

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event
{
    CGPoint location = point;
    location.x -= self.textContainerInset.left;
    location.y -= self.textContainerInset.top;
    CGFloat fraction = 0.0f;
    NSUInteger characterIndex = [self.layoutManager characterIndexForPoint:location
                                                           inTextContainer:self.textContainer
                                  fractionOfDistanceBetweenInsertionPoints:&fraction];
    if (!(fraction == 0.0 || fraction == 1.0) && characterIndex < self.textStorage.length) {
        if ([self.textStorage attribute:NSLinkAttributeName atIndex:characterIndex effectiveRange:NULL]) {
            return self;
        }
    }
    return nil;
}

@end
