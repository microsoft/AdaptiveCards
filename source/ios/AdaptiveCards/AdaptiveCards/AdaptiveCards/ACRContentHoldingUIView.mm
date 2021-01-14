//
//  ACRContentHoldingUIView
//  ACRContentHoldingUIView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRContentHoldingUIView.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACREnums.h"
#import "ACRUIImageView.h"
#import "ACRUILabel.h"
#import "SharedAdaptiveCard.h"
#import "UtiliOS.h"

const NSInteger eACRUILabelTag = 0x1234;
const NSInteger eACRUIFactSetTag = 0x1235;
const NSInteger eACRUIImageTag = 0x1236;

using namespace AdaptiveCards;

@implementation ACRContentHoldingUIView

- (CGSize)intrinsicContentSize
{
    return self.desiredContentSize;
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    if (_isPersonStyle) {
        UIView *subview = self.subviews[0];
        CGFloat radius = subview.bounds.size.width / 2.0;
        [subview.layer setCornerRadius:radius];
        [subview.layer setMasksToBounds:YES];
    }

    CGFloat width = self.frame.size.width;
    CGFloat height = self.frame.size.height;

    if (_isMediaType) {
        if (!_hidePlayIcon) {
            NSMutableArray<CALayer *> *shapes = [[NSMutableArray alloc] init];
            for (CALayer *layer in [self.layer sublayers]) {
                if ([[layer name] isEqualToString:@"circle"] ||
                    [[layer name] isEqualToString:@"triangle"]) {
                    [shapes addObject:layer];
                }
            }

            for (CALayer *layer in shapes) {
                [layer removeFromSuperlayer];
            }

            CGFloat radius = 30.0f;
            CGPoint centerPoint = CGPointMake((self.frame.size.width) / 2, (self.frame.size.height) / 2);

            UIBezierPath *circlePath = [UIBezierPath bezierPathWithOvalInRect:CGRectMake(centerPoint.x - radius, centerPoint.y - radius, 2 * radius, 2 * radius)];
            [circlePath closePath];
            CAShapeLayer *canvas = [[CAShapeLayer alloc] init];

            canvas.path = circlePath.CGPath;
            canvas.fillColor = UIColor.grayColor.CGColor;
            canvas.fillRule = kCAFillRuleNonZero;
            canvas.lineCap = kCALineCapButt;
            canvas.lineDashPattern = nil;
            canvas.lineDashPhase = 0.0;
            canvas.lineJoin = kCALineJoinMiter;
            canvas.lineWidth = 1.0;
            canvas.miterLimit = 10.0;
            canvas.strokeColor = canvas.fillColor;

            CGFloat triangleHeight = radius;
            CGFloat triangleSide = (2 / 1.731) * triangleHeight;
            CGFloat offset = 5.0f;

            UIBezierPath *trianglePath = [UIBezierPath bezierPath];
            [trianglePath moveToPoint:CGPointMake(centerPoint.x - triangleHeight / 2 + offset, centerPoint.y - triangleSide / 2)];
            [trianglePath addLineToPoint:CGPointMake(centerPoint.x + triangleHeight / 2 + offset, centerPoint.y)];
            [trianglePath addLineToPoint:CGPointMake(centerPoint.x - triangleHeight / 2 + offset, centerPoint.y + triangleSide / 2)];
            [trianglePath addLineToPoint:CGPointMake(centerPoint.x - triangleHeight / 2 + offset, centerPoint.y - triangleSide / 2)];
            [trianglePath closePath];

            CAShapeLayer *triangleCanvas = [[CAShapeLayer alloc] init];
            triangleCanvas.path = trianglePath.CGPath;
            triangleCanvas.fillColor = UIColor.whiteColor.CGColor;
            triangleCanvas.fillRule = kCAFillRuleNonZero;
            triangleCanvas.lineCap = kCALineCapButt;
            triangleCanvas.lineDashPattern = nil;
            triangleCanvas.lineDashPhase = 0.0;
            triangleCanvas.lineJoin = kCALineJoinMiter;
            triangleCanvas.lineWidth = 1.0;
            triangleCanvas.miterLimit = 10.0;
            triangleCanvas.strokeColor = canvas.fillColor;

            [canvas setName:@"circle"];
            [triangleCanvas setName:@"triangle"];
            [self.layer addSublayer:canvas];
            [self.layer addSublayer:triangleCanvas];
        } else {
            NSMutableArray<CALayer *> *shapes = [[NSMutableArray alloc] init];
            for (CALayer *layer in [self.layer sublayers]) {
                if ([[layer name] isEqualToString:@"circle"] ||
                    [[layer name] isEqualToString:@"triangle"]) {
                    [shapes addObject:layer];
                }
            }

            for (CALayer *layer in shapes) {
                [layer removeFromSuperlayer];
            }
        }
        // The content view is UIImageView
    } else {
        CGSize frameSize = self.frame.size;
        if (frameSize.width < self.desiredContentSize.width) {
            if (self.adaptiveImageSize == ACRImageSizeLarge || self.adaptiveImageSize == ACRImageSizeMedium || self.adaptiveImageSize == ACRImageSizeSmall || self.adaptiveImageSize == ACRImageSizeAuto || self.adaptiveImageSize == ACRImageSizeStretch) {
                CGSize ratios = getAspectRatio(self.desiredContentSize);
                height = width * ratios.height;
                width = frameSize.width;
                ((ACRUIImageView *)self.subviews[0]).desiredSize = self.desiredContentSize;
                self.desiredContentSize = self.frame.size;
                NSLayoutConstraint *hc = [self.heightAnchor constraintEqualToConstant:height];
                hc.priority = 999;
                hc.active = YES;
            }

        } else if (self.adaptiveImageSize == ACRImageSizeStretch and frameSize.width != self.desiredContentSize.width) {
            ACRUIImageView *imageView = (ACRUIImageView *)self.subviews[0];
            if (imageView.image) {
                CGSize ratios = getAspectRatio(imageView.image.size);
                height = width * ratios.height;
                width = frameSize.width;
                imageView.desiredSize = self.desiredContentSize;
                self.desiredContentSize = self.frame.size;
                NSLayoutConstraint *hc = [self.heightAnchor constraintEqualToConstant:height];
                hc.priority = 999;
                hc.active = YES;
                NSLayoutConstraint *hc2 = [self.subviews[0].heightAnchor constraintEqualToConstant:height];
                hc2.priority = 999;
                hc2.active = YES;
            }
        }
    }
}

@end
