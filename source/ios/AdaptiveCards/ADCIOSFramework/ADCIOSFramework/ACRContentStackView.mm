//
//  ACRkontentStackView
//  ACRContentStackView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#include "ACRContentStackView.h"

@implementation ACRContentStackView

- (instancetype) init 
{
    self = [super init];

    if(self) 
    { 
        [self config];
    } 

    return self;
}

- (instancetype) initWithCoder:(NSCoder *) aDecoder 
{
    self = [super initWithCoder:aDecoder];

    if (self) 
    {
        [self config];
    }

    return self;
}

- (void) config
{ 
    _stackView = [[UIStackView alloc] init];
    self.stackView.distribution = UIStackViewDistributionFillProportionally;
    [self addSubview: self.stackView];
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
}

- (CGSize) intrinsicContentSize
{
    return self.frame.size;
}

- (void)addArrangedSubview:(UIView *) view
{
    [self.stackView addArrangedSubview: view];
}

@end
