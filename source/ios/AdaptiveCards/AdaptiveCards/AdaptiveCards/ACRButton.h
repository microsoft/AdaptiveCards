//
//  ACRButton
//  ACRButton.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRView.h"

@interface UIButton(ACRButton)
+ (UIButton *)rootView:(ACRView *)rootView
     baseActionElement:(ACOBaseActionElement *)acoAction
                 title:(NSString *)title
               iconUrl:(NSString *)iconUrl
         andHostConfig:(ACOHostConfig *)config;
@end
