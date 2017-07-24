//
//  ACRContentHoldingUIView
//  ACRContentHoldingUIView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SharedAdaptiveCard.h"

@interface ACRContentHoldingUIView: UIView

- (NSArray* )setAlignment:(AdaptiveCards::HorizontalAlignment)alignment
            withSuperview:(UIView* )superview
                   toView:(UIView* )view;
@end
