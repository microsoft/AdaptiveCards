//
//  ACRTableCell.m
//  ACRTableCell
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRTableCellView.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"

@implementation ACRTableCellView {
    ACRTableCellDefinition *_definition;
}

- (instancetype)init:(ACOBaseCardElement *)baseCardElement
      cellDefinition:(ACRTableCellDefinition *)definition
            rootView:(ACRView *)rootView
              inputs:(NSMutableArray *)inputs
          hostConfig:(ACOHostConfig *)acoConfig;
{
    self = [super init];
    if (self) {
        if (definition) {
            _definition = definition;
        } else {
            _definition = [[ACRTableCellDefinition alloc] init];
        }                
        [self setAutoLayout];
        [self configureForStyle:acoConfig];
        if (rootView.context.isFirstRowAsHeaders) {
            self.accessibilityTraits |= UIAccessibilityTraitHeader;
        }
    }
    return self;
}

- (void)setAutoLayout
{
    self.translatesAutoresizingMaskIntoConstraints = NO;
//    _contentView.translatesAutoresizingMaskIntoConstraints = NO;
//    NSLayoutConstraint *contentViewWidthAnchor0 = [_contentView.widthAnchor constraintEqualToAnchor:self.widthAnchor];
//    NSLayoutConstraint *contentViewHeightAnchor0 = [_contentView.heightAnchor constraintLessThanOrEqualToAnchor:self.heightAnchor];
//    contentViewWidthAnchor0.priority = UILayoutPriorityRequired;
//    contentViewHeightAnchor0.priority = UILayoutPriorityRequired;
//    contentViewWidthAnchor0.active = YES;
//    contentViewHeightAnchor0.active = YES;

    [self setHorizontalAlignment];
//    [self setVerticalAlignment];
}

- (void)setHorizontalAlignment
{
    self.alignment = UIStackViewAlignmentCenter;
}

//- (void)setVerticalAlignment
//{
//    switch (_definition.verticalAlignment) {
//        case ACRVerticalContentAlignmentTop:
//            [_contentView.topAnchor constraintEqualToAnchor:self.topAnchor].active = YES;
//            break;
//        case ACRVerticalContentAlignmentCenter:
//            [_contentView.centerYAnchor constraintEqualToAnchor:self.centerYAnchor].active = YES;
//            break;
//        case ACRVerticalContentAlignmentBottom:
//            [_contentView.bottomAnchor constraintEqualToAnchor:self.bottomAnchor].active = YES;
//            break;
//    }
//}

- (void)configureForStyle:(ACOHostConfig *)acoConfig
{
    if (_definition) {
        CGFloat spacing = [acoConfig getHostConfig]->GetTable().cellSpacing;
        self.layoutMargins = UIEdgeInsetsMake(spacing, spacing, spacing, spacing);
        self.preservesSuperviewLayoutMargins = NO;
        self.preservesSuperviewLayoutMargins = NO;
        self.backgroundColor = [acoConfig getBackgroundColorForContainerStyle:_definition.style];
    }
}

//- (CGSize)intrinsicContentSize
//{
//    CGSize size = CGSizeMake(UIViewNoIntrinsicMetric, UIViewNoIntrinsicMetric);
//    if (_contentView) {
//        size = [_contentView intrinsicContentSize];
//    }
//    return size;
//}

- (void)addArrangedSubview:(UIView *)view
{
    [super addArrangedSubview:view];
    NSLayoutConstraint *constraint = nil;
    switch (_definition.horizontalAlignment) {
        case ACRLeft:
            constraint = [_stackView.leadingAnchor constraintEqualToAnchor:view.leadingAnchor];
            break;
        case ACRCenter:
            constraint = [_stackView.centerXAnchor constraintEqualToAnchor:view.centerXAnchor];
            break;
        case ACRRight:
            constraint = [_stackView.trailingAnchor constraintEqualToAnchor:view.trailingAnchor];
            break;
    }
    constraint.priority = 1000;
    constraint.active = YES;
//    [self addSubview:view];
}

@end

@implementation ACRTableCellDefinition

@end
