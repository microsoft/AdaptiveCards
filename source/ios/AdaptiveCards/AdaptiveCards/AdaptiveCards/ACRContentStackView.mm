//
//  ACRContentStackView
//  ACRContentStackView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#include "ACRContentStackView.h"

using namespace AdaptiveCards;

@implementation ACRContentStackView
{
    NSMutableArray* targets;
    ContainerStyle _style;
}

- (instancetype)init
{
    return [self initWithFrame:CGRectMake(0,0,0,0)];
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:CGRectMake(0,0,frame.size.width,0)];
    if(self)
    {
        _stackView = [[UIStackView alloc] initWithFrame:frame];
        [self config];
    }

    return self;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];

    if (self)
    {
        _stackView = [[UIStackView alloc] init];
        [self config];
    }

    return self;
}

- (ContainerStyle)getStyle(void)
{
    return _style;
}

- (void)setStyle:(ContainerStyle)style
{
    _style = style;
}

- (void)config
{
    if(!self.stackView) return;

    _style = ContainerStyle::None;

    [self addSubview:self.stackView];
    [self addConstraint:
     [NSLayoutConstraint constraintWithItem:self
                                  attribute:NSLayoutAttributeLeading
                                  relatedBy:NSLayoutRelationEqual
                                     toItem:self.stackView
                                  attribute:NSLayoutAttributeLeading
                                 multiplier:1
                                   constant:0]];
    [self addConstraint:
     [NSLayoutConstraint constraintWithItem:self
                                  attribute:NSLayoutAttributeTrailing
                                  relatedBy:NSLayoutRelationEqual
                                     toItem:self.stackView
                                  attribute:NSLayoutAttributeTrailing
                                 multiplier:1
                                   constant:0]];
    [self addConstraint:
     [NSLayoutConstraint constraintWithItem:self
                                  attribute:NSLayoutAttributeTop
                                  relatedBy:NSLayoutRelationEqual
                                     toItem:self.stackView
                                  attribute:NSLayoutAttributeTop
                                 multiplier:1
                                   constant:0]];
    [self addConstraint:
     [NSLayoutConstraint constraintWithItem:self
                                  attribute:NSLayoutAttributeBottom
                                  relatedBy:NSLayoutRelationEqual
                                     toItem:self.stackView
                                  attribute:NSLayoutAttributeBottom
                                 multiplier:1
                                   constant:0]];

    self.stackView.translatesAutoresizingMaskIntoConstraints = false;
    self.translatesAutoresizingMaskIntoConstraints = false;

    targets = [[NSMutableArray alloc] init];
}

- (CGSize)intrinsicContentSize
{
    return self.frame.size;
}

- (void)addArrangedSubview:(UIView *)view
{
    [self.stackView addArrangedSubview:view];
}

- (void)addTarget:(NSObject *)target
{
    [targets addObject:target];
}

// let the last element to strech
- (void)adjustHuggingForLastElement
{
    if([self.stackView.arrangedSubviews count])
        [[self.stackView.arrangedSubviews objectAtIndex:[self.stackView.arrangedSubviews count ] -1] setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
    if([self.stackView.arrangedSubviews count])
        [[self.stackView.arrangedSubviews objectAtIndex:[self.stackView.arrangedSubviews count ] -1] setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
}

- (UILayoutConstraintAxis) getAxis
{
    return self.stackView.axis;
}

@end
