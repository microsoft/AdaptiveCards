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
    CGFloat fraction = 20.0f;
    // find character under touch
    NSUInteger characterIndex = [self.layoutManager characterIndexForPoint:location inTextContainer:self.textContainer fractionOfDistanceBetweenInsertionPoints:&fraction];
    CGPoint endPoint =[self.layoutManager locationForGlyphAtIndex:[self.layoutManager glyphIndexForCharacterAtIndex:self.textStorage.length - 1]];
    CGFloat characterWidth = 2 * endPoint.x - [self.layoutManager locationForGlyphAtIndex:[self.layoutManager glyphIndexForCharacterAtIndex:self.textStorage.length - 2]].x;

    NSLog(@"character index x= %tu", characterIndex	);
    if (characterIndex < self.textStorage.length) {
        CGRect linesegment =
        [self.layoutManager lineFragmentRectForGlyphAtIndex:[self.layoutManager glyphIndexForCharacterAtIndex:self.textStorage.length - 1] effectiveRange:nil];
        NSLog(@"linesegment x = %f, y = %f, w = %f, h = %f", linesegment.origin.x, linesegment.origin.y, linesegment.size.width, linesegment.size.height);
        NSLog(@"location x= %f, y=%f", location.x, location.y);
        if(characterIndex == self.textStorage.length - 1 && location.x > characterWidth	){
            return nil;
        }
        NSURL *url = nil;
        url = [self.textStorage attribute:NSLinkAttributeName atIndex:characterIndex effectiveRange:NULL];
        if (url != nil) {
            return self;
        }
    }
    return nil;
}

@end
