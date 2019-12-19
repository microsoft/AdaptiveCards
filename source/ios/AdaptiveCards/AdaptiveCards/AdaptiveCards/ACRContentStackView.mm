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

static int kToggleVisibilityContext;

@implementation ACRContentStackView {
    NSMutableArray *_targets;
    NSMutableArray<ACRShowCardTarget *> *_showcardTargets;
    ACRContainerStyle _style;
    UIStackView *_stackView;
    NSMutableSet<UIView *> *_hiddenSubviews;
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
    if (self) {
        _hiddenSubviews = [[NSMutableSet alloc] init];
    }
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

- (UIStackViewAlignment)alignment
{
    return _stackView.alignment;
}

- (void)setAlignment:(UIStackViewAlignment)alignment
{
    _stackView.alignment = alignment;
}

- (UIStackViewDistribution)distribution
{
    return _stackView.distribution;
}

- (void)setDistribution:(UIStackViewDistribution)distribution
{
    _stackView.distribution = distribution;
}

- (UILayoutConstraintAxis)axis
{
    return _stackView.axis;
}

- (void)setAxis:(UILayoutConstraintAxis)axis
{
    _stackView.axis = axis;
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
    if (!_stackView) {
        return;
    }

    [self addSubview:_stackView];
    _stackView.translatesAutoresizingMaskIntoConstraints = NO;
    self.translatesAutoresizingMaskIntoConstraints = NO;
    _stackView.axis = self.axis;
    _stackView.distribution = self.distribution;
    _stackView.alignment = self.alignment;

    _targets = [[NSMutableArray alloc] init];
    _showcardTargets = [[NSMutableArray alloc] init];

    CGFloat top = 0, left = 0, bottom = 0, right = 0;

    if (attributes) {
        NSNumber *distribAttrib = attributes[@"distribution"];
        if ([distribAttrib boolValue]) {
            _stackView.distribution = (UIStackViewDistribution)[distribAttrib integerValue];
        }

        NSNumber *alignAttrib = attributes[@"alignment"];
        if ([alignAttrib boolValue]) {
            _stackView.alignment = (UIStackViewAlignment)[alignAttrib integerValue];
        }

        NSNumber *spacingAttrib = attributes[@"spacing"];
        if ([spacingAttrib boolValue]) {
            _stackView.spacing = [spacingAttrib floatValue];
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
    return self.combinedContentSize;
}

- (void)addArrangedSubview:(UIView *)view
{
    [_stackView addArrangedSubview:view];
    // if view is hidden before observer is added, we update hidden view count manually
    if (view.hidden) {
        [_hiddenSubviews addObject:view];
    }
    [view addObserver:self forKeyPath:@"hidden" options:NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld context:&kToggleVisibilityContext];
}

// it's hard to know collection to know when filling the collection is done, this method
// signals that the filling is done, and do the final visibility adjustment
- (void)hideIfSubviewsAreAllHidden
{
    NSInteger count = [_hiddenSubviews count];
    if (count and count == [_stackView.arrangedSubviews count]) {
        self.hidden = YES;
    }
}

- (void)observeValueForKeyPath:(NSString *)keyPath
                      ofObject:(id)object
                        change:(NSDictionary *)change
                       context:(void *)context
{
    if ([object isKindOfClass:[UIView class]]) {
        UIView *view = (UIView *)object;
        BOOL isHidden = view.hidden;
        if (isHidden == YES and ![_hiddenSubviews containsObject:view]) {
            [_hiddenSubviews addObject:view];
            [self decreaseIntrinsicContentSize:view];
            if ([_hiddenSubviews count] == [_stackView.arrangedSubviews count]) {
                self.hidden = YES;
            }
        } else {
            if ([_hiddenSubviews containsObject:view]) {
                [self increaseIntrinsicContentSize:view];
                [_hiddenSubviews removeObject:view];
                if (self.hidden) {
                    self.hidden = NO;
                }
            }
        }
    }
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
    if (view.hidden) {
        if ([_hiddenSubviews containsObject:view]) {
            [_hiddenSubviews removeObject:view];
        }
    }
    [view removeObserver:self forKeyPath:@"hidden"];
    [_stackView removeArrangedSubview:view];
    [view removeFromSuperview];
}

- (UIView *)getLastSubview
{
    UIView *view = nil;
    const NSUInteger subviewsCounts = [self subviewsCounts];
    if (subviewsCounts) {
        view = _stackView.subviews[subviewsCounts - 1];
    }
    return view;
}

- (UIView *)getLastArrangedSubview
{
    UIView *view = nil;
    const NSUInteger arrangedSubviewsCounts = [_stackView.arrangedSubviews count];
    if (arrangedSubviewsCounts) {
        view = _stackView.arrangedSubviews[arrangedSubviewsCounts - 1];
    }
    return view;
}

- (NSUInteger)subviewsCounts
{
    return [_stackView.subviews count];
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
    if ([_stackView.arrangedSubviews count])
        [[_stackView.arrangedSubviews objectAtIndex:[_stackView.arrangedSubviews count] - 1] setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
    if ([_stackView.arrangedSubviews count])
        [[_stackView.arrangedSubviews objectAtIndex:[_stackView.arrangedSubviews count] - 1] setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
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
                                                           topPadding, priority, bottomPadding, priority];

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

- (void)layoutSubviews
{
    [super layoutSubviews];

    if (_isActionSet) {
        float accumulatedWidth = 0, accumulatedHeight = 0, spacing = _stackView.spacing, maxWidth = 0, maxHeight = 0;

        for (UIView *view in _stackView.subviews) {
            accumulatedWidth += [view intrinsicContentSize].width;
            accumulatedHeight += [view intrinsicContentSize].height;
            maxWidth = MAX(maxWidth, [view intrinsicContentSize].width);
            maxHeight = MAX(maxHeight, [view intrinsicContentSize].height);
        }

        float contentWidth = accumulatedWidth, contentHeight = accumulatedHeight;
        if (_stackView.axis == UILayoutConstraintAxisHorizontal) {
            contentWidth += (_stackView.subviews.count - 1) * spacing;
            contentHeight = maxHeight;
        } else {
            contentHeight += (_stackView.subviews.count - 1) * spacing;
            contentWidth = maxWidth;
        }

        if (contentWidth > self.frame.size.width) {
            [self removeConstraints:_widthconstraint];
        }
    }
}

- (void)increaseIntrinsicContentSize:(UIView *)view
{
}

- (void)decreaseIntrinsicContentSize:(UIView *)view
{
}

- (CGFloat)getNextGreatHeight:(UIView *)view
{
    return [self getNextSize:view
                   dimension:^CGFloat(UIView *v) {
                       return [v intrinsicContentSize].height;
                   }];
}

- (CGFloat)getNextGreatWidth:(UIView *)view
{
    return [self getNextSize:view
                   dimension:^CGFloat(UIView *v) {
                       return [v intrinsicContentSize].width;
                   }];
}

- (CGFloat)getNextSize:(UIView *)view dimension:(CGFloat (^)(UIView *view))dimension
{
    CGFloat currentBest = 0.0;
    for (UIView *v in _stackView.arrangedSubviews) {
        if (![v isEqual:view]) {
            currentBest = MAX(currentBest, dimension(view));
        }
    }
    return currentBest;
}

- (void)dealloc
{
    for (UIView *view in _stackView.arrangedSubviews) {
        [view removeObserver:self forKeyPath:@"hidden"];
    }
}

@end
