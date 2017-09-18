//
//  ACRIContentHoldingView
//  ACRIContentHoldingView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@protocol ACRIContentHoldingView

- (void)addArrangedSubview:(UIView *)view;
- (UILayoutConstraintAxis)getAxis;
- (void)addTarget:(NSObject *)target;
- (void)adjustHuggingForLastElement;

@end
