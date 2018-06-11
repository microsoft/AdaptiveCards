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

@implementation ACRContentStackView
{
    NSMutableArray* _targets;
    NSMutableArray<ACRShowCardTarget *>* _showcardTargets;
    ACRContainerStyle _style;
}

- (instancetype)initWithStyle:(ACRContainerStyle)style
                  parentStyle:(ACRContainerStyle)parentStyle
                   hostConfig:(ACOHostConfig *)acoConfig
{
    self = [self initWithFrame:CGRectMake(0,0,0,0)];
    if(self){

        _style = style;
        if(style != ACRNone &&
            style != parentStyle) {
            std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
            [self setBackgroundColorWithHostConfig:config];
            [self setBorderColorWithHostConfig:config];
            [self setBorderThicknessWithHostConfig:config];
            [self removeConstraints:self.constraints];
            [self applyPadding:config->spacing.paddingSpacing priority:1000];
        }
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame attributes:(nullable NSDictionary<NSString *, id> *)attributes{
    self = [super initWithFrame:CGRectMake(0,0,frame.size.width,0)];
    if(self) {
        _stackView = [[UIStackView alloc] initWithFrame:frame];
        [self config:attributes];
    }
    return self;
}
- (instancetype)initWithFrame:(CGRect)frame
{
    self = [self initWithFrame:CGRectMake(0,0,frame.size.width,0) attributes:nil];
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];

    if (self)
    {
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

+ (UIColor *)colorFromString:(const std::string&)colorString
{
    long num = std::stoul(colorString.substr(1), nullptr, 16);

    return [UIColor colorWithRed:((num & 0x00FF0000) >> 16) / 255.0
                    green:((num & 0x0000FF00) >>  8) / 255.0
                     blue:((num & 0x000000FF)) / 255.0
                    alpha:((num & 0xFF000000) >> 24) / 255.0];
}

- (ContainerStyleDefinition&)paletteForHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    return (_style == ACREmphasis)
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
    const CGFloat borderWidth = [self paletteForHostConfig:config].borderThickness;

    [[self layer] setBorderWidth:borderWidth];
}

- (void)config:(nullable NSDictionary<NSString *, id> *)attributes
{
    if(!self.stackView){
        return;
    }
    [self addSubview:self.stackView];
    [self applyPadding:0 priority:1000];
    self.stackView.translatesAutoresizingMaskIntoConstraints = NO;
    self.translatesAutoresizingMaskIntoConstraints = NO;

    _targets = [[NSMutableArray alloc] init];
    _showcardTargets = [[NSMutableArray alloc] init];

    if(attributes){
        NSNumber *distribAttrib = attributes[@"distribution"];
        if(distribAttrib){
            self.stackView.distribution = (UIStackViewDistribution)[distribAttrib integerValue];
        }
        NSNumber *alignAttrib = attributes[@"alignment"];
        if(alignAttrib){
            self.stackView.alignment = (UIStackViewAlignment)[alignAttrib integerValue];
        }
        NSNumber *spacingAttrib = attributes[@"spacing"];
        if(spacingAttrib){
            self.stackView.spacing = [spacingAttrib floatValue];
        }
    }
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

    if([target isKindOfClass:[ACRShowCardTarget class]]){
        [_showcardTargets addObject:(ACRShowCardTarget *)target];
    }
}

- (void)hideAllShowCards
{
    for(ACRShowCardTarget *target in _showcardTargets){
        [target hideShowCard];
    }
}

// let the last element to strech
- (void)adjustHuggingForLastElement
{
    if([self.stackView.arrangedSubviews count])
        [[self.stackView.arrangedSubviews objectAtIndex:[self.stackView.arrangedSubviews count ] -1] setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
    if([self.stackView.arrangedSubviews count])
        [[self.stackView.arrangedSubviews objectAtIndex:[self.stackView.arrangedSubviews count ] -1] setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
}

- (void)applyPadding:(unsigned int)padding priority:(unsigned int)priority
{
    NSString *horString = [[NSString alloc] initWithFormat:@"H:|-(%u@%u)-[_stackView]-(%u@%u)-|",
                           padding, priority, padding, priority];
    NSString *verString = [[NSString alloc] initWithFormat:@"V:|-(%u@%u)-[_stackView]-(%u@%u)-|",
                           padding, priority, padding, priority];
    NSDictionary *dictionary = NSDictionaryOfVariableBindings(_stackView);
    NSArray *horzConst = [NSLayoutConstraint constraintsWithVisualFormat:horString
                                                                 options:0
                                                                 metrics:nil
                                                                   views:dictionary];
    NSArray *vertConst = [NSLayoutConstraint constraintsWithVisualFormat:verString
                                                                 options:0
                                                                 metrics:nil
                                                                   views:dictionary];
    [self addConstraints:horzConst];
    [self addConstraints:vertConst];
}

- (UILayoutConstraintAxis) getAxis
{
    return self.stackView.axis;
}

@end
