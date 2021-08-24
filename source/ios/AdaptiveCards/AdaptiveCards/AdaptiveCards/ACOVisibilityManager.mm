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
    NSHashTable<UIView *> *_paddingSet;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _paddingSet = [[NSHashTable alloc] initWithOptions:NSHashTableWeakMemory capacity:2];
    }
    return self;
}

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
    if (_paddingSet.count && [_columnWidth isEqualToString:@"auto"]) {
        for (UIView *subview in subviews) {
            if (!subview.isHidden && ![self isPadding:subview]) {
                return;
            }
        }

        [self changeVisibilitOfPaddingsTo:YES];
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
    BOOL isViewFound = NO, isLastView = YES, isPadding = NO;
    NSInteger targetIndex = subviews.count;
    NSUInteger visibleViewCounts = 0;
    for (NSInteger i = 0; i < subviews.count; i++) {
        UIView *subview = subviews[i];
        isPadding = [self isPadding:subview];
        if (!subview.isHidden && !isPadding) {
            visibleViewCounts += 1;
        }
        if ([subview isEqual:viewToBeUnhidden]) {
            targetIndex = i;
            isViewFound = YES;
            if (subview.isHidden) {
                visibleViewCounts += 1;
            }
        } else if (!subview.isHidden && isViewFound && (!_paddingSet.count || (!isPadding))) {
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
        
        if (visibleViewCounts > 1 && separator && separator.isHidden) {
            separator.hidden = NO;
        }

        if (isLastView && _paddingSet.count) {
            [self changeVisibilitOfPaddingsTo:NO];
        }
    }
}

- (void)addPadding:(UIView *)padding {
    if (padding && _paddingSet) {
        [_paddingSet addObject:padding];
    }
}

- (BOOL)isPadding:(UIView *)padding {
    if (padding && _paddingSet) {
        return [_paddingSet containsObject:padding];
    }
    return NO;
}

- (void)changeVisibilitOfPaddingsTo:(BOOL)visiblity
{
    for (UIView *padding in _paddingSet) {
        if (padding.isHidden != visiblity) {
            padding.hidden = visiblity;
        }
    }
}

@end
