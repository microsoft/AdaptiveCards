//
//  ACRUILabel.m
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRUILabel.h"
#import "ACRContentHoldingUIView.h"

@implementation ACRUILabel
const NSInteger eACRUILabelTag = 0x1234;
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
-(void)drawTextInRect:(CGRect)rect
{
    if (_isFactSetLabel || _isStretchable) {
        CGSize labelStringSize = [self.text boundingRectWithSize:CGSizeMake(self.frame.size.width, CGFLOAT_MAX)
                                                         options:NSStringDrawingUsesLineFragmentOrigin | NSStringDrawingUsesFontLeading
                                                      attributes:@{NSFontAttributeName:self.font}
                                                         context:nil].size;
        [super drawTextInRect:CGRectMake(0, 0, ceilf(self.frame.size.width),ceilf(labelStringSize.height))];
    } else {
        [super drawTextInRect:rect];
    }
}
*/


- (CGSize)intrinsicContentSize
{
    CGSize size = self.frame.size;
    self.scrollEnabled = YES;
    if(size.height != self.contentSize.height || size.width != self.contentSize.width) {
        [self sizeToFit];
    }
    size = self.frame.size;
    
    //CGSize size = [self.layoutManager usedRectForTextContainer:self.textContainer].size;
    self.scrollEnabled = NO;
    return size;
}

/*
- (void)updateConstraints
{
    CGSize size = self.frame.size;
    CGSize contentSize = self.contentSize;
    self.widthConstraint = [NSLayoutConstraint constraintWithItem:self attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationLessThanOrEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:size.width];
    self.heightConstraint = [NSLayoutConstraint constraintWithItem:self attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationLessThanOrEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:size.height];
    
    self.widthConstraint.priority = 999;
    self.widthConstraint.active = YES;
    self.heightConstraint.priority = 999;
    self.heightConstraint.active = YES;
    _area = contentSize.width * contentSize.height;
    [super updateConstraints];
}
 */

- (void)layoutSubviews
{
    [super layoutSubviews];
    if([self.superview isKindOfClass:[ACRContentHoldingUIView class]]) {
        CGSize size = self.frame.size;
        CGFloat area = size.width * size.height;
        if(area != _area){
            //[self setNeedsLayout];
            //[self invalidateIntrinsicContentSize];
            [self.superview invalidateIntrinsicContentSize];
            ((ACRContentHoldingUIView *)self.superview).bChanged = NO;
            _area = area;
        } else {
            ((ACRContentHoldingUIView *)self.superview).bChanged = NO;
        }
    }
}


@end
