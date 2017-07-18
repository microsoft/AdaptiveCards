//
//  ACRContentHoldingUIView
//  ACRContentHoldingUIView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SharedAdaptiveCard.h"

@interface ACRContentHoldingUIView: UIView

- (NSMutableArray*) setAlignment: (AdaptiveCards::HorizontalAlignment) alignment
                 withSuperview: (UIView*) superview
                        toView: (UIView*) view;
@end
