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

@implementation ACOVisibilityManager

- (void)hideView:(UIView *)viewToBeHidden arrangedSubviews:(NSArray<UIView *> *)subviews
{
    if (!subviews || !viewToBeHidden) {
        return;
    }

    if (!viewToBeHidden.isHidden) {
        viewToBeHidden.hidden = YES;
    }

    // get the index of the target view
    // if the target view is not the tail,
    // check to the right, and if the right separator and not hidden,
    // hide the separator
    // if the target view is tail, check to left, and if the left is separator and not hidden,
    // hide the separator
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

    // only cares for tailing padding at the moment
    // if column width is "auto", and all of its children hidden,
    // hide column, if is "stretch", then don't hide it.
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

- (void)unhideView:(UIView *)viewToBeUnhidden arrangedSubviews:(NSArray<UIView *> *)subviews
{
    if (!subviews || !viewToBeUnhidden) {
        return;
    }

    // find the index of target view and check if the view is at tail
    // if tail, check to left for separator else check to right
    // if trailing padding exists, the target view is tail and padding is hidden,
    // unhide the padding regardless
    BOOL isViewFound = NO, isLastView = YES;
    NSInteger targetIndex = subviews.count;
    for (NSInteger i = 0; i < subviews.count; i++) {
        UIView *subview = subviews[i];
        if ([subview isEqual:viewToBeUnhidden]) {
            targetIndex = i;
            isViewFound = YES;
        } else if (!subview.isHidden && isViewFound && (!self.padding || (self.padding && ![subview isEqual:self.padding]))) {
            isLastView = NO;
            break;
        }
    }

    if (isViewFound) {
        UIView *separator = nil;
        NSInteger separatorIndex = targetIndex;
        if (isLastView) {
            separatorIndex -= 1;
            if (separatorIndex > 0 && [subviews[separatorIndex] isKindOfClass:[ACRSeparator class]]) {
                separator = subviews[separatorIndex];
            }
        } else {
            separatorIndex += 1;
            if (separatorIndex < subviews.count && [subviews[separatorIndex] isKindOfClass:[ACRSeparator class]]) {
                separator = subviews[separatorIndex];
            }
        }

        UIView *targetView = subviews[targetIndex];
        if (targetView.isHidden) {
            targetView.hidden = NO;
        }
        if (separator && separator.isHidden) {
            separator.hidden = NO;
        }

        if (isLastView && self.padding && self.padding.isHidden) {
            self.padding.hidden = NO;
        }
    }
}

@end
