//
//  ACRButton
//  ACRButton.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRView.h"
#import <UIKit/UIKit.h>

@interface ACRButton : UIButton

@property IBInspectable NSNumber *positiveUseDefault;
@property IBInspectable UIColor *positiveForegroundColor;
@property IBInspectable UIColor *positiveBackgroundColor;
@property IBInspectable NSNumber *destructiveUseDefault;
@property IBInspectable UIColor *destructiveForegroundColor;
@property IBInspectable UIColor *destructiveBackgroundColor;
@property NSString *sentiment;
@property UIColor *defaultPositiveBackgroundColor;
@property UIColor *defaultDestructiveForegroundColor;
@property ACRIconPlacement iconPlacement;
@property __weak UIImageView *iconView;

+ (UIButton *)rootView:(ACRView *)rootView
     baseActionElement:(ACOBaseActionElement *)acoAction
                 title:(NSString *)title
         andHostConfig:(ACOHostConfig *)config;

- (void)setImageView:(UIImage *)image withConfig:(ACOHostConfig *)config;

- (void)applySentimentStyling;
@end
