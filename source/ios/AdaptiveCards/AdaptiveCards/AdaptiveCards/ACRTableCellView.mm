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
    __weak UIView *_contentView;
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

        [[ACRTableCellRenderer getInstance] render:self rootView:rootView inputs:inputs baseCardElement:baseCardElement hostConfig:acoConfig];
        _definition = definition;
        if ([self.subviews count]) {
            _contentView = self.subviews[0];
        }
        [self addSubview:_contentView];
        [self setAutoLayout];
        [self configureForStyle:acoConfig];
    }
    return self;
}

- (void)setAutoLayout
{
    if (_contentView) {
        NSLayoutConstraint *contentViewWidthAnchor0 = [_contentView.widthAnchor constraintLessThanOrEqualToAnchor:self.widthAnchor];
        NSLayoutConstraint *contentViewHeightAnchor0 = [_contentView.heightAnchor constraintLessThanOrEqualToAnchor:self.heightAnchor];
        NSLayoutConstraint *contentViewWidthAnchor1 = [_contentView.widthAnchor constraintEqualToAnchor:self.widthAnchor];
        NSLayoutConstraint *contentViewHeightAnchor1 = [_contentView.heightAnchor constraintEqualToAnchor:self.heightAnchor];
        contentViewWidthAnchor0.priority = UILayoutPriorityRequired;
        contentViewWidthAnchor1.priority = UILayoutPriorityFittingSizeLevel;
        contentViewHeightAnchor0.priority = UILayoutPriorityRequired;
        contentViewHeightAnchor1.priority = UILayoutPriorityFittingSizeLevel;
        contentViewWidthAnchor0.active = YES;
        contentViewWidthAnchor1.active = YES;
        contentViewHeightAnchor0.active = YES;
        contentViewHeightAnchor1.active = YES;

        [_contentView.leadingAnchor constraintEqualToAnchor:self.leadingAnchor].active = YES;
        [_contentView.topAnchor constraintEqualToAnchor:self.topAnchor].active = YES;
        self.translatesAutoresizingMaskIntoConstraints = NO;
        _contentView.translatesAutoresizingMaskIntoConstraints = NO;
    }
}

- (void)configureForStyle:(ACOHostConfig *)acoConfig
{
    if (_definition) {
        _spacing = [acoConfig getHostConfig]->GetTable().cellSpacing;
        self.layoutMargins = UIEdgeInsetsMake(_spacing, _spacing, _spacing, _spacing);
        _contentView.preservesSuperviewLayoutMargins = NO;
        self.preservesSuperviewLayoutMargins = NO;
        self.backgroundColor = [acoConfig getBackgroundColorForContainerStyle:_definition.style];
    }
}

- (CGSize)intrinsicContentSize
{
    CGSize size = CGSizeMake(UIViewNoIntrinsicMetric, UIViewNoIntrinsicMetric);
    if (_contentView) {
        size = [_contentView intrinsicContentSize];
    }
    return size;
}

@end

@implementation ACRTableCellDefinition

@end
