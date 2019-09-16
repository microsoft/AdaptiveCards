//
//  ACRContentStackView
//  ACRContentStackView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#include "ACRContentStackView.h"
#include "ACOHostConfigPrivate.h"
#import "ACRShowCardTarget.h"

using namespace AdaptiveCards;

@implementation ACRContentStackView {
    NSMutableArray *_targets;
    NSMutableArray<ACRShowCardTarget *> *_showcardTargets;
    ACRContainerStyle _style;
}

- (instancetype)initWithStyle:(ACRContainerStyle)style
                  parentStyle:(ACRContainerStyle)parentStyle
                   hostConfig:(ACOHostConfig *)acoConfig
                    superview:(UIView *)superview
{
    self = [self initWithFrame:superview.frame];
    if (self) {

        _style = style;
        if (style != ACRNone &&
            style != parentStyle) {
            std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
            self.backgroundColor = [acoConfig getBackgroundColorForContainerStyle:_style];
            [self setBorderColorWithHostConfig:config];
            [self setBorderThicknessWithHostConfig:config];
            [self removeConstraints:self.constraints];
            [self applyPadding:config->GetSpacing().paddingSpacing priority:1000];
        }
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame attributes:(nullable NSDictionary<NSString *, id> *)attributes
{
    self = [super initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height)];
    if (self) {
        _stackView = [[UIStackView alloc] initWithFrame:frame];
        [self config:attributes];
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [self initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height) attributes:nil];
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];

    if (self) {
        _stackView = [[UIStackView alloc] init];
        [self config:nil];
    }

    return self;
}

- (ACRContainerStyle)style
{
    return _style;
}

- (void)setStyle:(ACRContainerStyle)style
{
    _style = style;
}

+ (UIColor *)colorFromString:(const std::string &)colorString
{
    long num = std::stoul(colorString.substr(1), nullptr, 16);

    return [UIColor colorWithRed:((num & 0x00FF0000) >> 16) / 255.0
                           green:((num & 0x0000FF00) >> 8) / 255.0
                            blue:((num & 0x000000FF)) / 255.0
                           alpha:((num & 0xFF000000) >> 24) / 255.0];
}

- (void)setBackgroundColorWithHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    auto backgroundColor = config->GetBackgroundColor([ACOHostConfig getSharedContainerStyle:_style]);
    UIColor *color = [ACOHostConfig convertHexColorCodeToUIColor:backgroundColor];

    self.backgroundColor = color;
}

- (void)setBorderColorWithHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    auto borderColor = config->GetBorderColor([ACOHostConfig getSharedContainerStyle:_style]);
    UIColor *color = [ACOHostConfig convertHexColorCodeToUIColor:borderColor];

    [[self layer] setBorderColor:[color CGColor]];
}

- (void)setBorderThicknessWithHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    auto borderThickness = config->GetBorderThickness([ACOHostConfig getSharedContainerStyle:_style]);
    const CGFloat borderWidth = borderThickness;

    [[self layer] setBorderWidth:borderWidth];
}

- (void)config:(nullable NSDictionary<NSString *, id> *)attributes
{
    if (!self.stackView) {
        return;
    }

    [self addSubview:self.stackView];
    self.stackView.translatesAutoresizingMaskIntoConstraints = NO;
    self.translatesAutoresizingMaskIntoConstraints = NO;

    _targets = [[NSMutableArray alloc] init];
    _showcardTargets = [[NSMutableArray alloc] init];

    CGFloat top = 0, left = 0, bottom = 0, right = 0;

    if (attributes) {
        NSNumber *distribAttrib = attributes[@"distribution"];
        if ([distribAttrib boolValue]) {
            self.stackView.distribution = (UIStackViewDistribution)[distribAttrib integerValue];
        }

        NSNumber *alignAttrib = attributes[@"alignment"];
        if ([alignAttrib boolValue]) {
            self.stackView.alignment = (UIStackViewAlignment)[alignAttrib integerValue];
        }

        NSNumber *spacingAttrib = attributes[@"spacing"];
        if ([spacingAttrib boolValue]) {
            self.stackView.spacing = [spacingAttrib floatValue];
        }

        NSNumber *topPaddingAttrib = attributes[@"padding-top"];
        if ([topPaddingAttrib boolValue]) {
            top = [topPaddingAttrib floatValue];
        }
    }

    [self applyPaddingToTop:top
                       left:left
                     bottom:bottom
                      right:right
                   priority:1000
                   location:ACRBleedToAll];
}

- (CGSize)intrinsicContentSize
{
    return self.frame.size;
}

- (void)addArrangedSubview:(UIView *)view
{
    [self.stackView addArrangedSubview:view];
}

- (void)removeLastViewFromArrangedSubview
{
    if ([self subviewsCounts]) {
        UIView *view = [self getLastSubview];
        if (view) {
            [self removeViewFromContentStackView:view];
        }
    }
}

- (void)removeViewFromContentStackView:(UIView *)view
{
    [self.stackView removeArrangedSubview:view];
    [view removeFromSuperview];
}

- (UIView *)getLastSubview
{
    UIView *view = nil;
    const NSUInteger subviewsCounts = [self subviewsCounts];
    if (subviewsCounts) {
        view = self.stackView.subviews[subviewsCounts - 1];
    }
    return view;
}

- (NSUInteger)subviewsCounts
{
    return [self.stackView.subviews count];
}

- (void)addTarget:(NSObject *)target
{
    [_targets addObject:target];

    if ([target isKindOfClass:[ACRShowCardTarget class]]) {
        [_showcardTargets addObject:(ACRShowCardTarget *)target];
    }
}

- (void)hideAllShowCards
{
    for (ACRShowCardTarget *target in _showcardTargets) {
        [target hideShowCard];
    }
}

// let the last element to strech
- (void)adjustHuggingForLastElement
{
    if ([self.stackView.arrangedSubviews count])
        [[self.stackView.arrangedSubviews objectAtIndex:[self.stackView.arrangedSubviews count] - 1] setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
    if ([self.stackView.arrangedSubviews count])
        [[self.stackView.arrangedSubviews objectAtIndex:[self.stackView.arrangedSubviews count] - 1] setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
}

- (void)applyPadding:(unsigned int)padding priority:(unsigned int)priority
{
    [self applyPadding:padding priority:priority location:ACRBleedToAll];
}

- (void)applyPadding:(unsigned int)amount priority:(unsigned int)priority location:(ACRBleedDirection)location
{
    [self applyPaddingToTop:amount left:amount bottom:amount right:amount priority:priority location:location];
}

- (void)applyPaddingToTop:(CGFloat)top left:(CGFloat)left
                   bottom:(CGFloat)bottom
                    right:(CGFloat)right
                 priority:(unsigned int)priority
                 location:(ACRBleedDirection)location
{
    CGFloat leadingPadding = (location & ACRBleedToLeadingEdge) ? left : 0;
    CGFloat trailingPadding = (location & ACRBleedToTrailingEdge) ? right : 0;
    CGFloat topPadding = (location & ACRBleedToTopEdge) ? top : 0;
    CGFloat bottomPadding = (location & ACRBleedToBottomEdge) ? bottom : 0;

    NSString *horString = [[NSString alloc] initWithFormat:@"H:|-(%f@%u)-[_stackView]-(%f@%u)-|",
                                                           leadingPadding, priority, trailingPadding, priority];
    NSString *verString = [[NSString alloc] initWithFormat:@"V:|-(%f@%u)-[_stackView]-(%f@%u)-|",
                                                           topPadding, priority, bottomPadding, 999];

    NSDictionary *dictionary = NSDictionaryOfVariableBindings(_stackView);

    _widthconstraint = [NSLayoutConstraint constraintsWithVisualFormat:horString
                                                               options:0
                                                               metrics:nil
                                                                 views:dictionary];
    _heightconstraint = [NSLayoutConstraint constraintsWithVisualFormat:verString
                                                                options:0
                                                                metrics:nil
                                                                  views:dictionary];

    [self addConstraints:_widthconstraint];
    [self addConstraints:_heightconstraint];
}

// target is the background view, it will be pinned to parent according to the direction set by bleed,
// constraints that are specified by the direction, those will be set to the view that is bleeding
- (void)bleed:(unsigned int)padding priority:(unsigned int)priority target:(UIView *)target
     direction:(ACRBleedDirection)direction
    parentView:(UIView *)parent
{
    // remove existing constraints
    [self removeConstraints:_widthconstraint];
    [self removeConstraints:_heightconstraint];

    UIView *leadingView = (direction & ACRBleedToLeadingEdge) ? parent : self;
    UIView *trailingView = (direction & ACRBleedToTrailingEdge) ? parent : self;
    UIView *topView = (direction & ACRBleedToTopEdge) ? parent : self;
    UIView *bottomView = (direction & ACRBleedToBottomEdge) ? parent : self;

    [target.leadingAnchor constraintEqualToAnchor:leadingView.leadingAnchor].active = YES;
    [target.trailingAnchor constraintEqualToAnchor:trailingView.trailingAnchor].active = YES;
    [target.topAnchor constraintEqualToAnchor:topView.topAnchor].active = YES;
    [target.bottomAnchor constraintEqualToAnchor:bottomView.bottomAnchor].active = YES;

    // inverse the bit pattern that are set by ACRBleedDirection enums
    NSInteger bleedDirection = ~(~0 & direction);

    [self applyPadding:padding priority:1000 location:(ACRBleedDirection)bleedDirection];
}

- (UILayoutConstraintAxis)getAxis
{
    return self.stackView.axis;
}

- (void)layoutSubviews
{
    [super layoutSubviews];

    if (_isActionSet) {
        float accumulatedWidth = 0, accumulatedHeight = 0, spacing = self.stackView.spacing, maxWidth = 0, maxHeight = 0;

        for (UIView *view in self.stackView.subviews) {
            accumulatedWidth += [view intrinsicContentSize].width;
            accumulatedHeight += [view intrinsicContentSize].height;
            maxWidth = MAX(maxWidth, [view intrinsicContentSize].width);
            maxHeight = MAX(maxHeight, [view intrinsicContentSize].height);
        }

        float contentWidth = accumulatedWidth, contentHeight = accumulatedHeight;
        if (self.stackView.axis == UILayoutConstraintAxisHorizontal) {
            contentWidth += (self.stackView.subviews.count - 1) * spacing;
            contentHeight = maxHeight;
        } else {
            contentHeight += (self.stackView.subviews.count - 1) * spacing;
            contentWidth = maxWidth;
        }

        if (contentWidth > self.frame.size.width) {
            [self removeConstraints:_widthconstraint];
        }
    }
}

@end
