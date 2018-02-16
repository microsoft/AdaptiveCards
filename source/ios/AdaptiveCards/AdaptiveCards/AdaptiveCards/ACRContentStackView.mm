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
    NSMutableArray* _targets;
    ContainerStyle _style;
}

- (instancetype)initWithStyle:(ContainerStyle)style
                   hostConfig:(std::shared_ptr<HostConfig> const &)config
{
    self = [self initWithFrame:CGRectMake(0,0,0,0)];
    if(self)
    {
        _style = style;
        [self setBackgroundColorWithHostConfig:config];
        [self setBorderColorWithHostConfig:config];
        [self setBorderThicknessWithHostConfig:config];
    }
    return self;
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

- (ContainerStyle)getStyle
{
    return _style;
}

+ (UIColor *)colorFromString:(const std::string&)colorString
{
    long num = std::stoul(colorString.substr(1), nullptr, 16);

    return [UIColor colorWithRed:((num & 0x00FF0000) >> 16) / 255.0
                    green:((num & 0x0000FF00) >>  8) / 255.0
                     blue:((num & 0x000000FF)) / 255.0
                    alpha:((num & 0xFF000000) >> 24) / 255.0];
}

+ (CGFloat)borderWidthFromString:(const std::string&)thicknessString
{
    return std::stof(thicknessString);
}

- (ContainerStyleDefinition&)paletteForHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    return (_style == ContainerStyle::Emphasis)
        ? config->containerStyles.emphasisPalette
        : config->containerStyles.defaultPalette;
}

- (void)setBackgroundColorWithHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    UIColor *color = [[self class] colorFromString:[self paletteForHostConfig:config].backgroundColor];

    self.backgroundColor = color;
}

- (void)setBorderColorWithHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    UIColor *color = [[self class] colorFromString:[self paletteForHostConfig:config].borderColor];

    [[self layer] setBorderColor:[color CGColor]];
}

- (void)setBorderThicknessWithHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    const CGFloat borderWidth = [[self class] borderWidthFromString:[self paletteForHostConfig:config].borderThickness];

    [[self layer] setBorderWidth:borderWidth];
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

    _targets = [[NSMutableArray alloc] init];
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
    [_targets addObject:target];
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
