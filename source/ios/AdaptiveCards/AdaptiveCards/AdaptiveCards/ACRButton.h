//
//  ACRButton
//  ACRButton.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRView.h"

@interface ACRButton:UIButton

@property IBInspectable NSNumber *positiveUseDefault;
@property IBInspectable UIColor *positiveForegroundColor;
@property IBInspectable UIColor *positiveBackgroundColor;
@property IBInspectable NSNumber *destructiveUseDefault;
@property IBInspectable UIColor *destructiveForegroundColor;
@property IBInspectable UIColor *destructiveBackgroundColor;
@property ACRSentiment sentiment;
@property UIColor *defaultPositiveBackgroundColor;
@property UIColor *defaultDestructiveForegroundColor;

+ (UIButton *)rootView:(ACRView *)rootView
     baseActionElement:(ACOBaseActionElement *)acoAction
                 title:(NSString *)title
         andHostConfig:(ACOHostConfig *)config;

+ (void)setImageView:(UIImage*)image inButton:(UIButton*)button withConfig:(ACOHostConfig *)config contentSize:(CGSize)contentSize inconPlacement:(ACRIconPlacement)iconPlacement;

- (void)applySentimentStyling;
@end
