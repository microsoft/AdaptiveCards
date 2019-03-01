//
//  ACRUILabel.m
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRUILabel.h"
#import "ACRContentHoldingUIView.h"

@implementation ACRUILabel
{
    NSLayoutConstraint *widthConstraint;
    NSLayoutConstraint *heightConstraint;
}

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
    /*
    CGSize size = self.frame.size;
    self.scrollEnabled = YES;
    NSLog(@"superview w = %f, h = %f", self.superview.frame.size.width,
          self.superview.frame.size.height);
    
    //if(size.height != self.contentSize.height || size.width != self.contentSize.width) {
        [self sizeToFit];
     */
        /*
        NSLayoutConstraint *wconst = [NSLayoutConstraint constraintWithItem:self attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationLessThanOrEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:self.frame.size.width];
        NSLayoutConstraint *hconst = [NSLayoutConstraint constraintWithItem:self attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationLessThanOrEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:self.frame.size.height];
        if(!widthConstraint) {
            widthConstraint = wconst;
        } else {
            [self removeConstraint:widthConstraint];
            widthConstraint = wconst;
        }
        [self addConstraint:widthConstraint];
        if(!heightConstraint) {
            heightConstraint = hconst;
        } else {
            [self removeConstraint:heightConstraint];
            heightConstraint = hconst;
        }
        [self addConstraint:heightConstraint];
         
        [self layoutIfNeeded];
         */
    //}
    //size = self.frame.size;
/*
    self.scrollEnabled = NO;
    
    //NSLog(@"%@ text view h = %f, w = %f", self.attributedText, self.frame.size.height, self.frame.size.width);
    //return size;
    size = self.contentSize;
    _area = self.frame.size.width * self.frame.size.height;
    //size.width *= 2;
 */
    return self.frame.size;
}

- (void)layoutSubviews
{
    NSLog(@"TextView size w = %f, h = %f", self.frame.size.width, self.frame.size.height);
    CGSize size = self.frame.size;
    CGFloat area = size.width * size.height;
    //if(self.tag == eACRUILabelTag) {
        if(area != _area){
            _area = area;
            [self sizeToFit];
            _area = self.frame.size.width * self.frame.size.height;
            [self invalidateIntrinsicContentSize];
            //NSLog(@"intrinsic ContentSize changed");
            NSLog(@"text view calling invalidate intrinsic content size");
            //[self.superview invalidateIntrinsicContentSize];
            //[self.superview sizeToFit];
            //[self.rootView.acrActionDelegate didChangeViewLayout:CGRectZero newFrame:CGRectZero];

        }
    /*} else if(self.tag == eACRUIFactSetTag) {
        if(area != _area){
            _area = area;
            //[self invalidateIntrinsicContentSize];
            //[self.rootView.acrActionDelegate didChangeViewLayout:CGRectZero newFrame:CGRectZero];
        }
    }*/	
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
