//
//  ACRIContentHoldingView
//  ACRIContentHoldingView.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "ACRButtonTarget.h"

@protocol ACRIContentHoldingView

- (void)addArrangedSubview:(UIView *)view;
- (void)addTarget:(ACRButtonTarget *)target;
@end
