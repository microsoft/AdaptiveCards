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
    _stackView.distribution = UIStackViewDistributionFillProportionally;
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
