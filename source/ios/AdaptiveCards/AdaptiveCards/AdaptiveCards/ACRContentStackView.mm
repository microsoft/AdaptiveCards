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
    NSArray<NSLayoutConstraint *>* _widthconstraint;
    CGFloat _area;
}

- (instancetype)initWithStyle:(ACRContainerStyle)style
                  parentStyle:(ACRContainerStyle)parentStyle
                   hostConfig:(ACOHostConfig *)acoConfig
                    superview:(UIView *)superview
{
    self = [self initWithFrame:superview.frame];
    if(self){

        _style = style;
        if(style != ACRNone &&
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

- (instancetype)initWithFrame:(CGRect)frame attributes:(nullable NSDictionary<NSString *, id> *)attributes{
    self = [super initWithFrame:CGRectMake(0,0,frame.size.width, frame.size.height)];
    if(self) {
        //_stackView = [[UIStackView alloc] initWithFrame:frame];
        [self config:attributes];
    }
    return self;
}
- (instancetype)initWithFrame:(CGRect)frame
{
    self = [self initWithFrame:CGRectMake(0,0,frame.size.width, frame.size.height) attributes:nil];
    self.autoresizesSubviews = YES;
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];

    if (self)
    {
        //_stackView = [[UIStackView alloc] init];
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
    /*
    if(!self.stackView){
        return;
    }
     */
    //[self addSubview:self.stackView];
    [self applyPadding:0 priority:1000];
    //self.stackView.translatesAutoresizingMaskIntoConstraints = NO;
    self.translatesAutoresizingMaskIntoConstraints = NO;

    _targets = [[NSMutableArray alloc] init];
    _showcardTargets = [[NSMutableArray alloc] init];

    if(attributes){
        NSNumber *distribAttrib = attributes[@"distribution"];
        if([distribAttrib boolValue]){
            //self.stackView.distribution = (UIStackViewDistribution)[distribAttrib integerValue];
            self.distribution = (UIStackViewDistribution)[distribAttrib integerValue];
        }
        NSNumber *alignAttrib = attributes[@"alignment"];
        if([alignAttrib boolValue]){
            //self.stackView.alignment = (UIStackViewAlignment)[alignAttrib integerValue];
            self.alignment = (UIStackViewAlignment)[alignAttrib integerValue];
        }
        NSNumber *spacingAttrib = attributes[@"spacing"];
        if([spacingAttrib boolValue]){
            //self.stackView.spacing = [spacingAttrib floatValue];
            self.spacing = [spacingAttrib floatValue];
        }
    }
}

//- (CGSize)intrinsicContentSize
//{
/*
    NSLog(@"ACRContentStackView: dimension: w = %f, h = %f", self.frame.size.width, self.frame.size.height);
*/
    /*
    CGSize size = CGSizeZero;
    //if(self.stackView.axis == UILayoutConstraintAxisHorizontal) {
    if(self.axis == UILayoutConstraintAxisHorizontal) {
        //for(UIView *view in self.stackView.arrangedSubviews) {
        for(UIView *view in self.arrangedSubviews) {
            CGSize sizeOfSubView = [view intrinsicContentSize];
            size.width += sizeOfSubView.width;
            size.height = MAX(size.height, sizeOfSubView.height);
        }
    } else {
        //for(UIView *view in self.stackView.arrangedSubviews) {
        for(UIView *view in self.arrangedSubviews) {
            CGSize sizeOfSubView = [view intrinsicContentSize];
            size.height += sizeOfSubView.height;
            size.width = MAX(size.width, sizeOfSubView.width);
        }
    }
    _area = size.width * size.height;
     */
    /*
    if(size.width != self.frame.size.width || size.height != self.frame.size.height) {
        self.frame.size = size;
        //NSLog(@"ACRContentStackView StackView: dimension changed: w = %f, h = %f", size.width, size.height);
    }
    
    if(self.superview) {
        [self invalidateIntrinsicContentSize];
    }
 
    return self.frame.size;
    */
    /*
    size.height = 100;
    size.width = 180;
    */
//    CGSize size = [self systemLayoutSizeFittingSize:(UILayoutFittingCompressedSize)];
//    return size;
//}

- (void)addArrangedSubview:(UIView *)view
{
    //[self.stackView addArrangedSubview:view];
    [super addArrangedSubview:view];
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
//    if([self.stackView.arrangedSubviews count])
//        [[self.stackView.arrangedSubviews objectAtIndex:[self.stackView.arrangedSubviews count ] -1] setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
//    if([self.stackView.arrangedSubviews count])
//        [[self.stackView.arrangedSubviews objectAtIndex:[self.stackView.arrangedSubviews count ] -1] setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
    
    if([self.arrangedSubviews count])
        [[self.arrangedSubviews objectAtIndex:[self.arrangedSubviews count ] -1] setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
    if([self.arrangedSubviews count])
        [[self.arrangedSubviews objectAtIndex:[self.arrangedSubviews count ] -1] setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];

}

- (void)applyPadding:(unsigned int)padding priority:(unsigned int)priority
{
    if(self.superview) {
    NSString *horString = [[NSString alloc] initWithFormat:@"H:|-(%u@%u)-[self]-(%u@%u)-|",
                           padding, priority, padding, priority];
    NSString *verString = [[NSString alloc] initWithFormat:@"V:|-(%u@%u)-[self]-(%u@%u)-|",
                           padding, priority, padding, priority];
//    NSDictionary *dictionary = NSDictionaryOfVariableBindings(_stackView);
    NSDictionary *dictionary = NSDictionaryOfVariableBindings(self);
    _widthconstraint = [NSLayoutConstraint constraintsWithVisualFormat:horString
                                                                options:0
                                                                metrics:nil
                                                                  views:dictionary];
    NSArray *vertConst = [NSLayoutConstraint constraintsWithVisualFormat:verString
                                                                 options:0
                                                                 metrics:nil
                                                                   views:dictionary];
    [self addConstraints:_widthconstraint];
    [self addConstraints:vertConst];
    }
}

- (UILayoutConstraintAxis) getAxis
{
//    return self.stackView.axis;
    return self.axis;
}

- (void)layoutSubviews
{
    //NSLog(@"layout subviews before size w = %f, h = %f", self.frame.size.width, self.frame.size.height);
    
    [super layoutSubviews];
    
    //NSLog(@"layout subviews after size w = %f, h = %f", self.frame.size.width, self.frame.size.height);
    if (_isActionSet) {
//        float accumulatedWidth = 0, accumulatedHeight = 0, spacing = self.stackView.spacing, maxWidth = 0, maxHeight = 0;
        float accumulatedWidth = 0, accumulatedHeight = 0, spacing = self.spacing, maxWidth = 0, maxHeight = 0;

//        for(UIView *view in self.stackView.subviews){
            for(UIView *view in self.arrangedSubviews){
            accumulatedWidth += [view intrinsicContentSize].width;
            accumulatedHeight += [view intrinsicContentSize].height;
            maxWidth = MAX(maxWidth, [view intrinsicContentSize].width);
            maxHeight = MAX(maxHeight, [view intrinsicContentSize].height);
        }

        float contentWidth = accumulatedWidth, contentHeight = accumulatedHeight;
//        if(self.stackView.axis == UILayoutConstraintAxisHorizontal) {
          if(self.axis == UILayoutConstraintAxisHorizontal) {
//            contentWidth += (self.stackView.subviews.count - 1) * spacing;
              contentWidth += (self.arrangedSubviews.count - 1) * spacing;
            contentHeight = maxHeight;
        } else {
//            contentHeight += (self.stackView.subviews.count - 1) * spacing;
            contentHeight += (self.arrangedSubviews.count - 1) * spacing;
            contentWidth = maxWidth;
        }

        if (contentWidth > self.frame.size.width) {
            [self removeConstraints:_widthconstraint]; 
        }
    }
}

@end
