//
//  ACRSeparator.mm
//  ADCIOSFramework
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRSeparator.h"
#import "ACRContentStackView.h"
#import "HostConfig.h"
#import "TextBlock.h"

using namespace AdaptiveCards;

@implementation ACRSeparator
{
    CGFloat width;
    CGFloat height;
    CGFloat lineWidth;
    UILayoutConstraintAxis axis;
    long rgb;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:CGRectMake(0,0,0,0)];
    if(self)
    {
        width  = frame.size.width;
        height = frame.size.height;
        axis   = UILayoutConstraintAxisHorizontal;
        rgb    = 0;
        self.backgroundColor = UIColor.clearColor;
    }

    return self;
}

- (instancetype)initWithFrame:(CGRect)frame
                withSuperview:(UIView<ACRIContentHoldingView> *)superview
                       toAxis:(UILayoutConstraintAxis)huggingAxis

{
    self = [self initWithFrame:frame];
    if(self && superview)
    {
        axis = [superview getAxis];
        NSLayoutConstraint *constraints =
            [self configAutoLayout:superview havingAxis:axis toAxis:huggingAxis];
        [superview addArrangedSubview: self];

        if(constraints) [superview addConstraint:constraints];
    }
    else return nil;

    return self;
}

- (NSLayoutConstraint *)configAutoLayout:(UIView *)superview
                              havingAxis:(UILayoutConstraintAxis)superviewAxis
                                  toAxis:(UILayoutConstraintAxis)huggingAxis
{
    NSLayoutConstraint *constraint = nil;
    if(UILayoutConstraintAxisVertical == superviewAxis)
    {
        width  = MAX(width, superview.frame.size.width);
        constraint = [NSLayoutConstraint constraintWithItem:self
                                                  attribute:NSLayoutAttributeWidth
                                                  relatedBy:NSLayoutRelationEqual
                                                     toItem:superview
                                                  attribute:NSLayoutAttributeWidth
                                                 multiplier:1
                                                   constant:0];

    }
    else
    {
        height  = MAX(height, superview.frame.size.height);
        constraint = [NSLayoutConstraint constraintWithItem:self
                                                  attribute:NSLayoutAttributeHeight
                                                  relatedBy:NSLayoutRelationEqual
                                                     toItem:superview
                                                  attribute:NSLayoutAttributeHeight
                                                 multiplier:1
                                                   constant:0];
    }
    if(UILayoutConstraintAxisVertical == huggingAxis)
    {
        [self setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
        [self setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
    }
    else
    {
        [self setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
        [self setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
        [self setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
    }
    return constraint;
}

+ (void)renderSeparation:(std::shared_ptr<BaseCardElement> const &)elem
            forSuperview:(UIView *)view
          withHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    ACRSeparator *separator = nil;
    if(Spacing::None != elem->GetSpacing())
    {
        UIStackView *superview = nil;

        //clean-up in progress -- need to clean this up
        if([view isKindOfClass:[UIStackView class]])
        {
            superview = (UIStackView *) view;
        } else
        {
            superview = ((ACRContentStackView *) view).stackView;
        }

        separator = [[ACRSeparator alloc] init];
        unsigned int spacing = [separator getSpacing:elem withHostConfig:config];
        if(separator)
        {
            // Shared model has not implemented support
            separator->width  = spacing;
            separator->height = spacing;
            if(elem->GetSeparator())
            {
                separator->rgb		 = 0xB2000000;
                separator->lineWidth = 1;
            }

            separator.backgroundColor = UIColor.clearColor;
            [superview addArrangedSubview:separator];

            separator->axis = superview.axis;

            NSLayoutConstraint *constraint = [separator configAutoLayout:superview
                                                              havingAxis:superview.axis
                                                                  toAxis:superview.axis];

            if(constraint) [superview addConstraint:constraint];
        }
    }
}

- (unsigned int)getSpacing:(std::shared_ptr<BaseCardElement> const &)elem
                           withHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    switch (elem->GetSpacing())
    {
        case Spacing::ExtraLarge:
            return config->spacing.extraLargeSpacing;
        case Spacing::Large:
            return config->spacing.largeSpacing;
        case Spacing::Medium:
            return config->spacing.mediumSpacing;
        case Spacing::Small:
            return config->spacing.smallSpacing;
        case Spacing::Default:
            return config->spacing.defaultSpacing;
        default:
            break;
    }

    return 0;
}

- (void)drawRect:(CGRect)rect
{
    CGPoint orig, dest;
    if(UILayoutConstraintAxisVertical == self->axis)
    {
        orig = CGPointMake(rect.origin.x, rect.origin.y + rect.size.height / 2.0);
        dest = CGPointMake(rect.origin.x + rect.size.width,
                                          rect.origin.y + rect.size.height / 2.0);
    }
    else
    {
        orig = CGPointMake(rect.origin.x + rect.size.width / 2.0, rect.origin.y);
        dest = CGPointMake(rect.origin.x + rect.size.width / 2.0,
                                             rect.origin.y + rect.size.height);
    }

    UIBezierPath *path = [UIBezierPath bezierPath];
    if(path)
    {
        [path moveToPoint:   orig];
        [path addLineToPoint:dest];
        path.lineWidth =      self->lineWidth;

        [[UIColor colorWithRed:((self->rgb & 0x00FF0000)>> 16)/ 255.0
                         green:((self->rgb & 0x0000FF00)>> 8)/ 255.0
                          blue:((self->rgb & 0x000000FF))/ 255.0
                         alpha:((self->rgb & 0xFF000000)>> 24)/ 255.0] setStroke];

         [path stroke];
     }
}

- (CGSize)intrinsicContentSize
{
    return CGSizeMake(width, height);
}

@end
