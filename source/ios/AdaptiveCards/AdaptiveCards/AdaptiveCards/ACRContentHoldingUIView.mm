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
#import "ACRUILabel.h"
#import "SharedAdaptiveCard.h"
#import "UtiliOS.h"

const NSInteger eACRUILabelTag = 0x1234;
const NSInteger eACRUIFactSetTag = 0x1235;
const NSInteger eACRUIImageTag = 0x1236;

using namespace AdaptiveCards;

@implementation ACRContentHoldingUIView {
    __weak UIImageView *_imageView;
    __weak ACRContentStackView *_viewGroup;
    __weak NSLayoutConstraint *imageViewHeightConstraint;
    __weak NSLayoutConstraint *heightConstraint;
    BOOL isImageSet;
    CGSize prevIntrinsicContentSize;
}

- (instancetype)initWithImageProperties:(ACRImageProperties *)imageProperties imageView:(UIImageView *)imageView viewGroup:(ACRContentStackView *)viewGroup
{
    if (!imageProperties) {
        imageProperties = [[ACRImageProperties alloc] init];
    }

    CGRect frame = CGRectMake(0, 0, imageProperties.contentSize.width, imageProperties.contentSize.height);
    self = [super initWithFrame:frame];
    if (self) {
        self.imageProperties = imageProperties;
        _imageView = imageView;
        _viewGroup = viewGroup;
        [self addSubview:imageView];
        _contentView = imageView;
    }

    return self;
}

- (CGSize)intrinsicContentSize
{
    return self.imageProperties ? self.imageProperties.contentSize : [super intrinsicContentSize];
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
    } else {
        if (isImageSet || _imageView.image) {
            BOOL bUpdate = NO;
            if (self.imageProperties.acrImageSize != ACRImageSizeExplicit && !heightConstraint) {
                [self setHeightConstraint];
                bUpdate = YES;
            }

            if (self.imageProperties.acrImageSize == ACRImageSizeStretch) {
                bUpdate = !(heightConstraint && imageViewHeightConstraint);

                if (!heightConstraint) {
                    [self setHeightConstraint];
                }

                if (!imageViewHeightConstraint) {
                    [self setImageViewHeightConstraint];
                }
            }

            if (bUpdate) {
                if ([_viewGroup isKindOfClass:[ACRColumnView class]]) {
                    ACRColumnSetView *columnSetView = ((ACRColumnView *)_viewGroup).columnsetView;
                    if (columnSetView) {
                        [columnSetView updateIntrinsicContentSize];
                        [columnSetView invalidateIntrinsicContentSize];
                    }
                }
                [_viewGroup invalidateIntrinsicContentSize];
            }
        }
    }
}

// update the intrinsic content size when the width become available
- (void)updateIntrinsicContentSizeOfSelfAndViewGroup
{
    CGFloat width = self.imageProperties.contentSize.width;
    if (self.imageProperties.acrImageSize == ACRImageSizeStretch || (width > self.frame.size.width)) {
        width = self.frame.size.width;
    }

    CGFloat height = 1.0f;

    CGSize ratios = getAspectRatio(self.imageProperties.contentSize);
    height = width * ratios.height;

    // adjust intrinsic contentsize of superview
    // substract the previous intrinsic content size from the view group
    [_viewGroup decreaseIntrinsicContentSize:self];
    // update it to the new value
    self.imageProperties.contentSize = CGSizeMake(width, height);
    // increase the view group's intrinsic content size by the new ICS
    [_viewGroup increaseIntrinsicContentSize:self];
}

- (void)update:(ACRImageProperties *)imageProperties
{
    isImageSet = YES;
    if (imageProperties) {
        self.imageProperties = imageProperties;
        [self invalidateIntrinsicContentSize];
    }
}

- (void)setHeightConstraint
{
    [self updateIntrinsicContentSizeOfSelfAndViewGroup];
    heightConstraint = [self setHeightConstraintUtil:self.heightAnchor];
}

- (void)setImageViewHeightConstraint
{
    // set new height anchor to the height of new intrinsic contentsize
    imageViewHeightConstraint = [self setHeightConstraintUtil:_imageView.heightAnchor];
}

- (NSLayoutConstraint *)setHeightConstraintUtil:(NSLayoutDimension *)heightAnchor
{
    NSLayoutConstraint *constraint = [heightAnchor constraintEqualToConstant:self.imageProperties.contentSize.height];
    constraint.priority = 999;
    constraint.active = YES;
    return constraint;
}

@end
