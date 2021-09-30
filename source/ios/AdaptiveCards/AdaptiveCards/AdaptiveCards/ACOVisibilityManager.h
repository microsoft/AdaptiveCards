//
//  ACOVisibilityManager.h
//  AdaptiveCards
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOFillerSpaceManager.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol ACOIVisibilityManagerFacade <NSObject>

- (void)hideView:(UIView *)view;
- (void)unhideView:(UIView *)view;
- (void)updatePaddingVisibility;

@end

@class ACRContentStackView;

@interface ACOVisibilityManager : NSObject

@property (nonatomic) BOOL hasVisibleViews;

- (instancetype)init:(ACOFillerSpaceManager *)fillerSpaceManager;

/// hide `viewToBeHidden`. `hostView` is a superview of type ColumnView or ColumnSetView
- (void)hideView:(UIView *)viewToBeHidden hostView:(ACRContentStackView *)hostView;

/// unhide `viewToBeUnhidden`. `hostView` is a superview of type ColumnView or ColumnSetView
- (void)unhideView:(UIView *)viewToBeUnhidden hostView:(ACRContentStackView *)hostView;

/// change the visibility of the padding of a host view to `visibility`
/// `visibility` `YES` indicates that the padding will be hidden
- (void)changeVisibilityOfPadding:(UIView *)hostView visibilityHidden:(BOOL)visibility;

- (void)updatePaddingVisibility;

/// adds index of a visible view to a visible views collection, and the index is maintained in sorted order
/// in increasing order.
- (void)addVisibleView:(NSUInteger)index;

@end
