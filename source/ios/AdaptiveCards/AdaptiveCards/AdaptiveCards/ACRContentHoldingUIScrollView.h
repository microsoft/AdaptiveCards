//
//  ACRContentHoldingUIScrollView
//  ACRContentHoldingUIScrollView.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ACRContentHoldingUIScrollView: UIScrollView

@property BOOL stretch;
@property BOOL isContentSizeConstraintSet;
@property UIStackView *contentview;
@property CGFloat spacing;
@property CGFloat contentWidth;
@property NSLayoutConstraint *widthConstraintForStretch;
@property NSLayoutConstraint *centerXConstraintForStretch;
@property NSLayoutConstraint *centerYConstraintForStretch;

@end
