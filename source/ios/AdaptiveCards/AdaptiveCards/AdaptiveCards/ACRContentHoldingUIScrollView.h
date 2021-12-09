//
//  ACRContentHoldingUIScrollView
//  ACRContentHoldingUIScrollView.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ACRContentHoldingUIScrollView : UIScrollView

@property BOOL stretch;
@property BOOL isContentSizeConstraintSet;
@property UIStackView *contentview;
@property CGFloat spacing;
@property CGFloat contentWidth;

// collection of constraints that will be used when
// buttons will only occupy just enough space
@property NSArray<NSLayoutConstraint *> *nonStretchConstraints;
// collection of constraints that will be used when buttons will
// streteched to fill the available width
@property NSArray<NSLayoutConstraint *> *stretchConstraints;

- (void)preconfigreAutolayout;

@end
