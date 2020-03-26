//
//  ACRContentHoldingUIScrollView
//  ACRContentHoldingUIScrollView.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ACRContentHoldingUIScrollView : UIScrollView

@property bool stretch;
@property UIView *contentview;
@property CGFloat contentWidth;

@end
