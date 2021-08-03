//
//  ACOVisibilityManager.mm
//  AdaptiveCards
//
//  Copyright © 2021 Microsoft. All rights reserved.
//
//

#import "ACOVisibilityManager.h"
#import "ACREnums.h"
#import "ACRSeparator.h"

@implementation ACOVisibilityManager {
    NSString *_columnWidth;
}

- (instancetype)init:(NSDictionary *)properties
{
    self = [self init];
    if (self) {

        if (properties) {
            _columnWidth = properties[@"columnWidth"];
        }
    }
    return self;
}

- (void)hideView:(UIView *)viewToBeHidden arrangedSubviews:(NSArray<UIView *> *)subviews
{
    if (!subviews || !subviews) {
        return;
    }

    if (!viewToBeHidden.isHidden) {
        viewToBeHidden.hidden = YES;
    }

    NSInteger index = [subviews indexOfObject:viewToBeHidden];
    if (index + 1 < subviews.count) {
        NSInteger nextViewIndex = index + 1;
        UIView *nextView = subviews[nextViewIndex];
        if ([nextView isKindOfClass:[ACRSeparator class]]) {
            if (!nextView.isHidden) {
                nextView.hidden = YES;
            }
        }
    } else if (index - 1 >= 0) {
        NSInteger prevViewIndex = index - 1;
        UIView *prevView = subviews[prevViewIndex];
        if ([prevView isKindOfClass:[ACRSeparator class]]) {
            if (!prevView.isHidden) {
                prevView.hidden = YES;
            }
        }
    }

    if (self.padding && [_columnWidth isEqualToString:@"auto"]) {
        for (UIView *subview in subviews) {
            if (!subview.isHidden && ![subview isEqual:self.padding]) {
                return;
            }
        }

        if (!self.padding.isHidden) {
            self.padding.hidden = YES;
        }
    }
}

@end
