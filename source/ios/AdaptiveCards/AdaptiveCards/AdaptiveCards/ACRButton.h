//
//  ACRButton
//  ACRButton.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRView.h"

@interface UIButton(ACRButton)

@property (nonatomic) NSNumber *positiveUseDefault;
@property (nonatomic) UIColor *positiveForegroundColor;
@property (nonatomic) UIColor *positiveBackgroundColor;
@property (nonatomic) NSNumber *destructiveUseDefault;
@property (nonatomic) UIColor *destructiveForegroundColor;
@property (nonatomic) UIColor *destructiveBackgroundColor;

+ (UIButton *)rootView:(ACRView *)rootView
     baseActionElement:(ACOBaseActionElement *)acoAction
                 title:(NSString *)title
         andHostConfig:(ACOHostConfig *)config;

+ (void)setImageView:(UIImage*)image inButton:(UIButton*)button withConfig:(ACOHostConfig *)config contentSize:(CGSize)contentSize inconPlacement:(ACRIconPlacement)iconPlacement;
@end
