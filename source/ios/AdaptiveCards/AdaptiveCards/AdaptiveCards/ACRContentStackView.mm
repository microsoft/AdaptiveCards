//
//  ACRContentStackView
//  ACRContentStackView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#include "ACRContentStackView.h"
#include "ACOHostConfigPrivate.h"

using namespace AdaptiveCards;

@implementation ACRContentStackView
{
    NSMutableArray* _targets;
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

- (void)config
{
    if(!self.stackView){
        return;
    }
    [self addSubview:self.stackView];
    [self applyPadding:0 priority:1000];
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
