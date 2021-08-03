//
//  ACOVisibilityManager.h
//  AdaptiveCards
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface ACOVisibilityManager : NSObject

@property (weak) UIView *padding;

- (instancetype)init:(NSDictionary *)properties;

/// hides viewToBeHidden from arrangedSubViews 
- (void)hideView:(UIView *)viewToBeHidden arrangedSubviews:(NSArray<UIView *> *)subviews;

@end
