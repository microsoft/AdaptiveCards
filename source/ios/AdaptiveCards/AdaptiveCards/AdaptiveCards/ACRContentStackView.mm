//
//  ACRContentStackView
//  ACRContentStackView.mm
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#include "ACRContentStackView.h"
#import "ACOBaseCardElementPrivate.h"
#include "ACOHostConfigPrivate.h"
#import "ACRShowCardTarget.h"
#import "ACRViewPrivate.h"
#import "UtiliOS.h"

using namespace AdaptiveCards;

@implementation ACRContentStackView {
    NSMutableArray *_targets;
    NSMutableArray<ACRShowCardTarget *> *_showcardTargets;
    ACRContainerStyle _style;
    NSMutableDictionary<NSString *, NSValue *> *_subviewIntrinsicContentSizeCollection;
    ACRRtl _rtl;
    NSMutableSet *_invisibleViews;
    ACRVerticalContentAlignment _verticalContentAlignment;
    ACRHorizontalAlignment _horizontalAlignment;
}

- (instancetype)initWithStyle:(ACRContainerStyle)style
                  parentStyle:(ACRContainerStyle)parentStyle
                   hostConfig:(ACOHostConfig *)acoConfig
                    superview:(UIView *)superview
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    self = [self initWithFrame:superview.frame attributes:nil];
    if (self) {
        _style = style;
        if (style != ACRNone &&
            style != parentStyle) {
            self.backgroundColor = [acoConfig getBackgroundColorForContainerStyle:_style];
            [self setBorderColorWithHostConfig:config];
            [self setBorderThicknessWithHostConfig:config];
            [self removeConstraints:self.constraints];
            [self applyPadding:config->GetSpacing().paddingSpacing priority:1000];
        }
    }
    return self;
}

// this is the dedicated initializer
- (instancetype)initWithFrame:(CGRect)frame attributes:(nullable NSDictionary<NSString *, id> *)attributes
{
    self = [super initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height)];
    if (self) {
        _stackView = [[UIStackView alloc] init];
        _subviewIntrinsicContentSizeCollection = [[NSMutableDictionary alloc] init];
        _paddingHandler = [[ACOFillerSpaceManager alloc] init];
        _visibilityManager = [[ACOVisibilityManager alloc] init:_paddingHandler];
        _paddings = [[NSMutableArray alloc] init];
        self.clipsToBounds = NO;
        [self config:attributes];
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    return [self initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height) attributes:nil];
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

- (void)setRtl:(ACRRtl)rtl
{
    _rtl = rtl;
    if (!_stackView || rtl == ACRRtlNone) {
        return;
    }

    _stackView.semanticContentAttribute = (rtl == ACRRtlRTL) ? UISemanticContentAttributeForceRightToLeft : UISemanticContentAttributeForceLeftToRight;
}

- (ACRRtl)rtl
{
    return _rtl;
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

        NSNumber *paddingSpacing = attributes[@"padding-spacing"];
        if ([paddingSpacing boolValue]) {
            top = left = bottom = right = [paddingSpacing floatValue];
        }

        NSNumber *topPaddingAttrib = attributes[@"padding-top"];
        if ([topPaddingAttrib boolValue]) {
            top = [topPaddingAttrib floatValue];
        }

        NSNumber *horizontalAlignment = attributes[@"horizontal-alignment"];
        if ([horizontalAlignment intValue]) {
            _horizontalAlignment = (ACRHorizontalAlignment)[horizontalAlignment intValue];
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

- (void)updateIntrinsicContentSize
{
}

- (void)updateIntrinsicContentSize:(void (^)(UIView *view, NSUInteger idx, BOOL *stop))block
{
    [_stackView.arrangedSubviews enumerateObjectsUsingBlock:block];
}

- (NSArray<UIView *> *)getArrangedSubviews
{
    return _stackView.arrangedSubviews;
}

- (NSArray<UIView *> *_Nonnull)getContentStackSubviews
{
    return _stackView.subviews;
}

- (void)addArrangedSubview:(UIView *)view
{
    if (view) {
        [_stackView addArrangedSubview:view];
    }
}

- (void)insertArrangedSubview:(UIView *)view atIndex:(NSUInteger)insertionIndex
{
    if (view) {
        [_stackView insertArrangedSubview:view atIndex:insertionIndex];
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

- (NSUInteger)arrangedSubviewsCounts
{
    return [_stackView.arrangedSubviews count];
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

- (void)applyPaddingToTop:(CGFloat)top
                     left:(CGFloat)left
                   bottom:(CGFloat)bottom
                    right:(CGFloat)right
                 priority:(unsigned int)priority
                 location:(ACRBleedDirection)location
{
    CGFloat leadingPadding = (location & ACRBleedToLeadingEdge) ? left : 0;
    CGFloat trailingPadding = (location & ACRBleedToTrailingEdge) ? right : 0;
    CGFloat topPadding = (location & ACRBleedToTopEdge) ? top : 0;
    CGFloat bottomPadding = (location & ACRBleedToBottomEdge) ? bottom : 0;

    NSMutableArray<NSLayoutConstraint *> *constraints = [[NSMutableArray alloc] init];
    NSDictionary *dictionary = nil;

    if (_horizontalAlignment == ACRRight || _horizontalAlignment == ACRCenter) {
        UILayoutGuide *leftSpacer = [[UILayoutGuide alloc] init];
        [self addLayoutGuide:leftSpacer];
        [constraints addObject:[self.centerYAnchor constraintEqualToAnchor:leftSpacer.centerYAnchor]];
        NSLayoutConstraint *leftSpacerWidthConstraint = [leftSpacer.widthAnchor constraintEqualToConstant:0];
        leftSpacerWidthConstraint.priority = UILayoutPriorityDefaultLow;
        [constraints addObject:leftSpacerWidthConstraint];
        if (_horizontalAlignment == ACRCenter) {
            UILayoutGuide *rightSpacer = [[UILayoutGuide alloc] init];
            [self addLayoutGuide:rightSpacer];
            [constraints addObject:[self.centerYAnchor constraintEqualToAnchor:rightSpacer.centerYAnchor]];
            NSLayoutConstraint *rightSpacerWidthConstraint = [rightSpacer.widthAnchor constraintEqualToConstant:0];
            rightSpacerWidthConstraint.priority = UILayoutPriorityDefaultLow;
            [constraints addObject:rightSpacerWidthConstraint];
            [constraints addObject:[rightSpacer.widthAnchor constraintEqualToAnchor:leftSpacer.widthAnchor]];
            dictionary = NSDictionaryOfVariableBindings(_stackView, rightSpacer, leftSpacer);
        } else {
            dictionary = NSDictionaryOfVariableBindings(_stackView, leftSpacer);
        }
    } else {
        dictionary = NSDictionaryOfVariableBindings(_stackView);
    }

    NSString *leftSpacerStr = (_horizontalAlignment == ACRRight || _horizontalAlignment == ACRCenter) ? @"[leftSpacer]-" : @"";
    NSString *rightSpacerStr = (_horizontalAlignment == ACRCenter) ? @"[rightSpacer]-" : @"";

    NSString *horString = [[NSString alloc] initWithFormat:@"H:|-(%f@%u)-%@[_stackView]-%@(%f@%u)-|",
                                                           leadingPadding, priority, leftSpacerStr, rightSpacerStr, trailingPadding, priority];
    NSString *verString = [[NSString alloc] initWithFormat:@"V:|-(%f@%u)-[_stackView]-(%f@%u)-|",
                                                           topPadding, priority, bottomPadding, priority];

    _widthconstraint = [NSLayoutConstraint constraintsWithVisualFormat:horString
                                                               options:0
                                                               metrics:nil
                                                                 views:dictionary];
    _heightconstraint = [NSLayoutConstraint constraintsWithVisualFormat:verString
                                                                options:0
                                                                metrics:nil
                                                                  views:dictionary];

    [constraints addObjectsFromArray:_widthconstraint];
    [constraints addObjectsFromArray:_heightconstraint];

    [NSLayoutConstraint activateConstraints:constraints];
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

    // inverse the bit pattern that are set by ACRBleedDirection enums
    NSInteger bleedDirection = ~(~0 & direction);

    [self applyPadding:padding priority:1000 location:(ACRBleedDirection)bleedDirection];

    CGFloat paddingInFloat = padding;
    CGFloat top = (direction & ACRBleedToTopEdge) ? -paddingInFloat : 0;
    CGFloat leading = (direction & ACRBleedToLeadingEdge) ? -paddingInFloat : 0;
    CGFloat bottom = (direction & ACRBleedToBottomEdge) ? -paddingInFloat : 0;
    CGFloat trailing = (direction & ACRBleedToTrailingEdge) ? -paddingInFloat : 0;

    if (@available(iOS 11.0, *)) {
        self.directionalLayoutMargins = NSDirectionalEdgeInsetsMake(top, leading, bottom, trailing);
    } else {
        self.layoutMargins = UIEdgeInsetsMake(top, leading, bottom, trailing);
    }

    [target.topAnchor constraintEqualToAnchor:self.layoutMarginsGuide.topAnchor].active = YES;
    [target.leadingAnchor constraintEqualToAnchor:self.layoutMarginsGuide.leadingAnchor].active = YES;
    [target.trailingAnchor constraintEqualToAnchor:self.layoutMarginsGuide.trailingAnchor].active = YES;

    if (parent && (direction & ACRBleedToBottomEdge)) {
        [target.bottomAnchor constraintEqualToAnchor:parent.bottomAnchor].active = YES;
    } else {
        [target.bottomAnchor constraintEqualToAnchor:self.layoutMarginsGuide.bottomAnchor].active = YES;
    }
}

- (void)layoutSubviews
{
    [super layoutSubviews];

    if ([self.subviews count]) {
        // configures background when this view contains a background image, and does only once
        NSMutableArray<NSLayoutConstraint *> *constraints = [[NSMutableArray alloc] init];
        renderBackgroundCoverMode(self.subviews[0], self.backgroundView, constraints, self);
        [NSLayoutConstraint activateConstraints:constraints];
    }

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
    NSString *key = [NSString stringWithFormat:@"%p", view];
    _subviewIntrinsicContentSizeCollection[key] = [NSValue valueWithCGSize:[view intrinsicContentSize]];
}

- (CGSize)getIntrinsicContentSizeInArragedSubviews:(UIView *)view
{
    if (not view) {
        return CGSizeZero;
    }
    NSString *key = [NSString stringWithFormat:@"%p", view];
    NSValue *value = _subviewIntrinsicContentSizeCollection[key];
    return value ? [value CGSizeValue] : CGSizeZero;
}

- (void)decreaseIntrinsicContentSize:(UIView *)view
{
}

- (CGFloat)getMaxHeightOfSubviewsAfterExcluding:(UIView *)view
{
    return [self getViewWithMaxDimensionAfterExcluding:view
                                             dimension:^CGFloat(UIView *v) {
                                                 NSString *key = [NSString stringWithFormat:@"%p", v];
                                                 NSValue *value = self->_subviewIntrinsicContentSizeCollection[key];
                                                 return (value ? [value CGSizeValue] : CGSizeZero).height;
                                             }];
}

- (CGFloat)getMaxWidthOfSubviewsAfterExcluding:(UIView *)view
{
    return [self getViewWithMaxDimensionAfterExcluding:view
                                             dimension:^CGFloat(UIView *v) {
                                                 NSString *key = [NSString stringWithFormat:@"%p", v];
                                                 NSValue *value = self->_subviewIntrinsicContentSizeCollection[key];
                                                 return (value ? [value CGSizeValue] : CGSizeZero).width;
                                             }];
}

- (CGFloat)getViewWithMaxDimensionAfterExcluding:(UIView *)view dimension:(CGFloat (^)(UIView *view))dimension
{
    CGFloat currentBest = 0.0;
    for (UIView *v in _stackView.arrangedSubviews) {
        if (![v isEqual:view]) {
            currentBest = MAX(currentBest, dimension(v));
        }
    }
    return currentBest;
}

- (void)configureForSelectAction:(ACOBaseActionElement *)action rootView:(ACRView *)rootView
{
    if (action != nullptr) {
        NSObject<ACRSelectActionDelegate> *target = nil;
        if (ACRRenderingStatus::ACROk == buildTarget([rootView getSelectActionsTargetBuilderDirector], action, &target)) {
            [self addTarget:target];
            self.selectActionTarget = target;
            setAccessibilityTrait(self, action);
        }
    }
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    if (self.selectActionTarget) {
        return;
    } else {
        [self.nextResponder touchesBegan:touches withEvent:event];
    }
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    if (self.selectActionTarget) {
        [self.selectActionTarget doSelectAction];
    } else {
        [self.nextResponder touchesEnded:touches withEvent:event];
    }
}

// use this method if a subview to the content stack view needs a padding
// use configureHeightFor for all cases except when stretching the subview
// is not desirable.
- (UIView *)addPaddingFor:(UIView *)view
{
    return [_paddingHandler addPaddingFor:view];
}

- (UIView *)addPaddingSpace
{
    UIView *blankTrailingSpace = [[UIView alloc] init];
    blankTrailingSpace.translatesAutoresizingMaskIntoConstraints = NO;
    [blankTrailingSpace setContentHuggingPriority:UILayoutPriorityDefaultLow - 10 forAxis:UILayoutConstraintAxisVertical];
    [self addArrangedSubview:blankTrailingSpace];
    return blankTrailingSpace;
}

/// it simply adds padding to the top and bottom of contents of the content stack view
/// according to vertical alignment
- (void)addPadding
{
    if (_verticalContentAlignment == ACRVerticalContentAlignmentCenter ||
        _verticalContentAlignment == ACRVerticalContentAlignmentBottom) {
        [_paddings addObject:[self addPaddingFor:self]];
        [self insertArrangedSubview:_paddings.lastObject atIndex:0];
    }

    if (_verticalContentAlignment == ACRVerticalContentAlignmentCenter ||
        (_verticalContentAlignment == ACRVerticalContentAlignmentTop &&
         self.distribution == UIStackViewDistributionFill)) {
        [_paddings addObject:[self addPaddingFor:self]];
        [self addArrangedSubview:_paddings.lastObject];
    }
}

- (void)updatePaddingVisibility
{
    if ([self shouldAddPadding:self.hasStretchableView]) {
        [self addPadding];
    }

    [_visibilityManager changeVisibilityOfPadding:self visibilityHidden:!_visibilityManager.hasVisibleViews];

    [_visibilityManager updatePaddingVisibility];
}

- (void)hideView:(UIView *)view
{
    [_visibilityManager hideView:view hostView:self];
}

- (void)unhideView:(UIView *)view
{
    [_visibilityManager unhideView:view hostView:self];
}

- (BOOL)hasStretchableView
{
    return _paddingHandler.hasPadding;
}

- (void)registerInvisibleView:(UIView *)invisibleView
{
    if (!_invisibleViews) {
        _invisibleViews = [[NSMutableSet alloc] init];
    }

    [_invisibleViews addObject:invisibleView];
}

/// this method applies visibility to subviews once all of them are rendered and become part of content stack view
/// applying visibility as each subview is rendered has known side effects.
/// such as its superview, content stack view becomes hidden if a first subview is set hidden.
- (void)applyVisibilityToSubviews
{
    for (NSUInteger i = 0; i < _stackView.subviews.count; i++) {
        UIView *subview = _stackView.subviews[i];
        if (![_paddingHandler isPadding:subview] && ![subview isKindOfClass:[ACRSeparator class]]) {
            [_visibilityManager addVisibleView:i];
        }
    }

    for (UIView *subview in _invisibleViews) {
        [_visibilityManager hideView:subview hostView:self];
    }
}

- (void)configureHeightFor:(UIView *)view acoElement:(ACOBaseCardElement *)element
{
    [_paddingHandler configureHeight:view correspondingElement:element];
}

/// this function will tell if the content stack view should have a padding
/// padding will be added if
/// none of its subviews is stretchable or has padding and there is at least
/// one visible view.
/// the content stack view has hasStrechableView property, but getting the property value
/// has cost, so added the hasStretcahbleView parameter to reduce the number of call to
/// the property value.
- (BOOL)shouldAddPadding:(BOOL)hasStretchableView
{
    return (!hasStretchableView && _visibilityManager.hasVisibleViews);
}

- (void)associateSeparatorWithOwnerView:(ACRSeparator *)separator ownerView:(UIView *)ownerView
{
    if (!separator) {
        return;
    }
    [_paddingHandler associateSeparatorWithOwnerView:separator ownerView:ownerView];
}

/// call this method after subview is rendered
/// it configures height, creates association between the subview and its separator if any
/// registers subview for its visibility
- (void)updateLayoutAndVisibilityOfRenderedView:(UIView *)renderedView
                                     acoElement:(ACOBaseCardElement *)acoElem
                                      separator:(ACRSeparator *)separator
                                       rootView:(ACRView *)rootView
{
    if (!renderedView) {
        return;
    }

    [self configureHeightFor:renderedView acoElement:acoElem];
    [self associateSeparatorWithOwnerView:separator ownerView:renderedView];

    NSString *hashkey = [NSString stringWithCString:acoElem.element->GetId().c_str()
                                           encoding:NSUTF8StringEncoding];
    renderedView.tag = hashkey.hash;

    [rootView.context registerVisibilityManager:self targetViewTag:renderedView.tag];

    if (!acoElem.element->GetIsVisible()) {
        [self registerInvisibleView:renderedView];
    }
}

/// call this method once all subviews are rendered
/// this methods add padding to itself for alignment and stretch
/// apply visibility to subviews
/// configure min height
/// then activate all contraints associated with the configuration.
/// activation constraint all at once is more efficient than activating
/// constraints one by one.
- (void)configureLayoutAndVisibility:(ACRVerticalContentAlignment)verticalContentAlignment
                           minHeight:(NSInteger)minHeight
                          heightType:(ACRHeightType)heightType
                                type:(ACRCardElementType)type
{
    _verticalContentAlignment = verticalContentAlignment;

    [self applyVisibilityToSubviews];

    BOOL isStretchable = self.hasStretchableView;

    if ([self shouldAddPadding:isStretchable]) {
        [self addPadding];
    }

    if (minHeight > 0) {
        NSLayoutConstraint *constraint =
            [NSLayoutConstraint constraintWithItem:self
                                         attribute:NSLayoutAttributeHeight
                                         relatedBy:NSLayoutRelationGreaterThanOrEqual
                                            toItem:nil
                                         attribute:NSLayoutAttributeNotAnAttribute
                                        multiplier:1
                                          constant:minHeight];
        constraint.priority = 999;
        constraint.active = YES;
    }

    [_paddingHandler activateConstraintsForPadding];
}

@end
