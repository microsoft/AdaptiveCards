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

- (CGSize)intrinsicContentSize
{
    return self.frame.size;
}

- (void)layoutSubviews
{
    /*if (self.tag == eACRUILabelTag && self.frame.size.height != self.contentSize.height) {
        
        NSLayoutConstraint *heightconst =
        [NSLayoutConstraint constraintWithItem:self attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:self.contentSize.height];        
        //heightconst.active = YES;
        [self sizeToFit];
    } else */ if (self.tag == eACRUIFactSetTag) {
        CGFloat area = self.frame.size.height * self.frame.size.width;
        if (area != _area) {
            [self invalidateIntrinsicContentSize];
            _area = area;
        }
    }
    [super layoutSubviews];
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
