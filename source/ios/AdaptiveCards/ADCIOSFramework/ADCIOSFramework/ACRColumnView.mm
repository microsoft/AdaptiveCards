//
//  ACRColumnView
//  ACRColumnView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#include "ACRColumnView.h"

@implementation ACRColumnView

-(void)config
{
    [super config];
    super.stackView.axis = UILayoutConstraintAxisVertical;
}

- (void)addArrangedSubview:(UIView *) view
{
    [super addArrangedSubview: view];
}

@end
