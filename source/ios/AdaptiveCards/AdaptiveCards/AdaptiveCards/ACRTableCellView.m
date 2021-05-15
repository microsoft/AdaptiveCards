//
//  ACRTableCell.m
//  SPMTest
//
//  Created by Inyoung Woo on 5/14/21.
//

#import "ACRTableCellView.h"

@implementation ACRTableCellView {
    __weak UIView *_contentView;
    ACRTableCellDefinition *_definition;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

- (instancetype)init:(UIView *)content cellDefinition:(ACRTableCellDefinition *)definition
{
    self = [super init];
    if (self) {
        _contentView = content;
        _definition = definition;
        [self addSubview:content];
        [self setAutoLayout];
        [self configureForStyle];
        _spacing = 8.0f;
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

- (void)configHorizontalAlignment
{
}

- (void)configureForStyle
{
    if (_definition) {
        self.layoutMargins = UIEdgeInsetsMake(8.0f, 8.0f, 8.0f, 8.0f);
        self.backgroundColor = [UIColor grayColor];
        _contentView.preservesSuperviewLayoutMargins = NO;
        self.preservesSuperviewLayoutMargins = NO;
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

@implementation ACRTableCellDefinition {
    ACRHorizontalAlignment _horizontalAlignment;
    ACRContainerStyle _style;
}

- (instancetype)init:(ACRHorizontalAlignment)horizontalAlignment
{
    self = [super init];
    if (self) {
        _horizontalAlignment = horizontalAlignment;
    }
    return self;
}

@end
