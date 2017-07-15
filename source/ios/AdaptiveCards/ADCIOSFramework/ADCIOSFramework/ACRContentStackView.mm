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
    [self addConstraint:
     [NSLayoutConstraint constraintWithItem:self
                                  attribute:NSLayoutAttributeTop
                                  relatedBy:NSLayoutRelationEqual
                                     toItem:self.stackView
                                  attribute:NSLayoutAttributeTop
                                 multiplier:1
                                   constant:0]];
    [self addConstraint:
     [NSLayoutConstraint constraintWithItem:self
                                  attribute:NSLayoutAttributeBottom
                                  relatedBy:NSLayoutRelationEqual
                                     toItem:self.stackView
                                  attribute:NSLayoutAttributeBottom
                                 multiplier:1
                                   constant:0]];
    
    self.stackView.translatesAutoresizingMaskIntoConstraints = false;
    self.translatesAutoresizingMaskIntoConstraints = false;
}

- (CGSize) intrinsicContentSize
{
    NSLog(@"%@, w = %f, h = %f", self, self.frame.size.width, self.frame.size.height);
    return self.frame.size;
}

- (void)addArrangedSubview:(UIView *) view
{
    [self.stackView addArrangedSubview: view];
}

@end
