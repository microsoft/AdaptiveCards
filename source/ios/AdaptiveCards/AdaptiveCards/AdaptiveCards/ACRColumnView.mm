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
    //self.stackView.axis = UILayoutConstraintAxisVertical;
    self.axis = UILayoutConstraintAxisVertical;
    [super config:attributes];
}

- (void)addArrangedSubview:(UIView *)view
{
    // if auto, maintain content size whenever possible
    if([self.columnWidth isEqualToString:@"auto"]){
        [view setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
      // if columnWidth is set to stretch or number, allow column to fill the available space
    } else {
        [view setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
        [view setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
    }

//    [self.stackView addArrangedSubview:view];
    [super addArrangedSubview:view];
}

- (UIView *)addPaddingSpace
{
    UIView *blankTrailingSpace = [[UIView alloc] init];
    [blankTrailingSpace setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
    [super addArrangedSubview:blankTrailingSpace];
    return blankTrailingSpace;
}

@end
