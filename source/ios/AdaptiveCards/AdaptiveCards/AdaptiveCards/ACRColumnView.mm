//
//  ACRColumnView
//  ACRColumnView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnView.h"

@implementation ACRColumnView

- (void)config:(nullable NSDictionary<NSString *, id> *)attributes
{
    super.stackView.axis = UILayoutConstraintAxisVertical;
    super.stackView.distribution = UIStackViewDistributionFill;
    [super config:attributes];
}

- (void)addArrangedSubview:(UIView *)view
{
    // if columnWidth is set to stretch, allows to fill the available space
    if([self.columnWidth isEqualToString:@"stretch"]){
        [view setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
    } // if auto, maintain content size whenever possible
    else if([self.columnWidth isEqualToString:@"auto"]){
        [view setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
    }
    [self.stackView addArrangedSubview:view];
}

@end
