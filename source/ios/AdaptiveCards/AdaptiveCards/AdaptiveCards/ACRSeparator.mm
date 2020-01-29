//
//  ACRSeparator.mm
//  ADCIOSFramework
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRSeparator.h"
#import "ACRContentStackView.h"
#import "HostConfig.h"
#import "TextBlock.h"
#import <UIKit/UIKit.h>

using namespace AdaptiveCards;

@implementation ACRSeparator {
    CGFloat width;
    CGFloat height;
    CGFloat lineWidth;
    UILayoutConstraintAxis axis;
    long rgb;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        width = frame.size.width;
        height = frame.size.height;
        axis = UILayoutConstraintAxisHorizontal;
        rgb = 0;
        self.backgroundColor = UIColor.clearColor;
    }

    return self;
}

+ (void)renderSeparationWithFrame:(CGRect)frame
                        superview:(UIView<ACRIContentHoldingView> *)superview
                             axis:(UILayoutConstraintAxis)huggingAxis
{
    ACRSeparator *separator = [[ACRSeparator alloc] initWithFrame:frame];
    if (separator && superview) {
        separator->axis = ((ACRContentStackView *)superview).axis;
        NSLayoutConstraint *constraints =
            [separator configAutoLayout:superview
                             havingAxis:separator->axis
                                 toAxis:huggingAxis];
        [superview addArrangedSubview:separator];

        if (constraints)
            [superview addConstraint:constraints];
    }
}

- (NSLayoutConstraint *)configAutoLayout:(UIView *)superview
                              havingAxis:(UILayoutConstraintAxis)superviewAxis
                                  toAxis:(UILayoutConstraintAxis)huggingAxis
{
    NSLayoutConstraint *constraint = nil;
    if (UILayoutConstraintAxisVertical == superviewAxis) {
        width = MAX(width, superview.frame.size.width);
        constraint = [NSLayoutConstraint constraintWithItem:self
                                                  attribute:NSLayoutAttributeWidth
                                                  relatedBy:NSLayoutRelationEqual
                                                     toItem:superview
                                                  attribute:NSLayoutAttributeWidth
                                                 multiplier:1
                                                   constant:0];

    } else {
        height = MAX(height, superview.frame.size.height);
        constraint = [NSLayoutConstraint constraintWithItem:self
                                                  attribute:NSLayoutAttributeHeight
                                                  relatedBy:NSLayoutRelationEqual
                                                     toItem:superview
                                                  attribute:NSLayoutAttributeHeight
                                                 multiplier:1
                                                   constant:0];
    }

    NSLayoutConstraint *constraintByAnchor = nil;

    if (UILayoutConstraintAxisVertical == huggingAxis) {
        [self setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
        [self setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
        constraintByAnchor = [self.heightAnchor constraintEqualToConstant:height];
    } else {
        [self setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
        [self setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
        constraintByAnchor = [self.widthAnchor constraintEqualToConstant:width];
    }

    constraintByAnchor.priority = 999;
    constraintByAnchor.active = YES;
    constraint.priority = 999;
    return constraint;
}

+ (void)renderActionsSeparator:(UIView *)view
                    hostConfig:(std::shared_ptr<HostConfig> const &)config
{
    std::shared_ptr<BaseCardElement> nullBaseCardElem;
    [ACRSeparator renderSeparation:nullBaseCardElem
                         superview:view
                        hostConfig:config
                           spacing:config->GetActions().spacing];
}

+ (ACRSeparator *)renderSeparation:(std::shared_ptr<BaseCardElement> const &)elem
                      forSuperview:(UIView *)view
                    withHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    return [ACRSeparator renderSeparation:elem superview:view hostConfig:config spacing:Spacing::None];
}

+ (ACRSeparator *)renderSeparation:(std::shared_ptr<BaseCardElement> const &)elem
                         superview:(UIView *)view
                        hostConfig:(std::shared_ptr<HostConfig> const &)config
                           spacing:(Spacing)spacing
{
    ACRSeparator *separator = nil;
    Spacing requestedSpacing = Spacing::None;

    if (elem) {
        requestedSpacing = elem->GetSpacing();
    } else {
        requestedSpacing = spacing;
    }

    if (Spacing::None != requestedSpacing) {
        ACRContentStackView *superview = (ACRContentStackView *)view;
        unsigned int spacing = [ACRSeparator getSpacing:requestedSpacing hostConfig:config];
        separator = [[ACRSeparator alloc] initWithFrame:CGRectMake(0, 0, spacing, spacing)];

        if (separator) {
            // Shared model has not implemented support
            separator->width = spacing;
            separator->height = spacing;
            if (elem && elem->GetSeparator()) {
                separator->rgb = std::stoul(config->GetSeparator().lineColor.substr(1), nullptr, 16);
                separator->lineWidth = config->GetSeparator().lineThickness;
                ;
            }

            separator.backgroundColor = UIColor.clearColor;
            [superview addArrangedSubview:separator];

            separator->axis = superview.axis;

            NSLayoutConstraint *constraint = [separator configAutoLayout:superview
                                                              havingAxis:superview.axis
                                                                  toAxis:superview.axis];

            if (constraint) {
                [superview addConstraint:constraint];
            }
        }
    }

    return separator;
}

+ (unsigned int)getSpacing:(Spacing)spacing hostConfig:(std::shared_ptr<HostConfig> const &)config
{
    switch (spacing) {
        case Spacing::ExtraLarge:
            return config->GetSpacing().extraLargeSpacing;
        case Spacing::Large:
            return config->GetSpacing().largeSpacing;
        case Spacing::Medium:
            return config->GetSpacing().mediumSpacing;
        case Spacing::Small:
            return config->GetSpacing().smallSpacing;
        case Spacing::Default:
            return config->GetSpacing().defaultSpacing;
        default:
            break;
    }

    return 0;
}

- (void)drawRect:(CGRect)rect
{
    CGPoint orig, dest;
    if (UILayoutConstraintAxisVertical == self->axis) {
        orig = CGPointMake(rect.origin.x, rect.origin.y + rect.size.height / 2.0);
        dest = CGPointMake(rect.origin.x + rect.size.width,
                           rect.origin.y + rect.size.height / 2.0);
    } else {
        orig = CGPointMake(rect.origin.x + rect.size.width / 2.0, rect.origin.y);
        dest = CGPointMake(rect.origin.x + rect.size.width / 2.0,
                           rect.origin.y + rect.size.height);
    }

    UIBezierPath *path = [UIBezierPath bezierPath];
    if (path) {
        [path moveToPoint:orig];
        [path addLineToPoint:dest];
        path.lineWidth = self->lineWidth;

        [[UIColor colorWithRed:((self->rgb & 0x00FF0000) >> 16) / 255.0
                         green:((self->rgb & 0x0000FF00) >> 8) / 255.0
                          blue:((self->rgb & 0x000000FF)) / 255.0
                         alpha:((self->rgb & 0xFF000000) >> 24) / 255.0] setStroke];

        [path stroke];
    }
}

- (CGSize)intrinsicContentSize
{
    return CGSizeMake(width, height);
}

@end
