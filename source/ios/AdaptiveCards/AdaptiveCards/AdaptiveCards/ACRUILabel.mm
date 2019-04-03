//
//  ACRUILabel.m
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRUILabel.h"
#import "ACRContentHoldingUIView.h"
#import "ACRAggregateTarget.h"

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
    CGSize size = self.frame.size;
    self.scrollEnabled = YES;

    if(size.height != self.contentSize.height || size.width != self.contentSize.width) {
        [self sizeToFit];
    }
    size = self.frame.size;

    self.scrollEnabled = NO;
    return size;
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    CGSize size = self.frame.size;
    CGFloat area = size.width * size.height;
    if(self.tag == eACRUILabelTag) {
        if(area != _area){
            [self.superview invalidateIntrinsicContentSize];
        }
    } else if(self.tag == eACRUIFactSetTag) {
        if(area != _area){
            [self invalidateIntrinsicContentSize];
        }
    }
    _area = area;
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
        if ([self.textStorage attribute:NSLinkAttributeName atIndex:characterIndex effectiveRange:NULL] ||
            [self.textStorage attribute:@"SelectAction" atIndex:characterIndex effectiveRange:NULL]) {
            return self;
        }
    }
    return nil;
}

- (void)handleInlineAction:(UIGestureRecognizer *)gestureRecognizer
{
    ACRUILabel *view = (ACRUILabel *)gestureRecognizer.view;
    
    CGPoint pt = [gestureRecognizer locationInView:view];
    pt.x -= view.textContainerInset.left;
    pt.y -= view.textContainerInset.top;
    
    NSUInteger indexAtChar = [[view layoutManager] characterIndexForPoint:pt inTextContainer:view.textContainer fractionOfDistanceBetweenInsertionPoints:NULL];
    if(indexAtChar < view.textStorage.length) {
        id target = [view.attributedText attribute:@"SelectAction" atIndex:indexAtChar effectiveRange:nil];
        if([target respondsToSelector:@selector(doSelectAction)]) {
            [target doSelectAction];
        }
    }
}

@end
