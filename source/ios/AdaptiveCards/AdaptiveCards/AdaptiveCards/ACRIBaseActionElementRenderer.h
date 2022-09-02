//
//  ACRIBaseActionElementRenderer
//  ACRIBaseActionElementRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACOBaseActionElement.h>
#import <AdaptiveCards/ACOHostConfig.h>
#import <AdaptiveCards/ACRView.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol ACRIBaseActionElementRenderer

- (UIButton *)renderButton:(ACRView *)rootView
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig;
@end

@protocol ACRIBaseActionSetRenderer

- (UIView *)renderButtons:(ACRView *)rootView
                   inputs:(NSMutableArray *)inputs
                superview:(UIView<ACRIContentHoldingView> *)superview
                     card:(ACOAdaptiveCard *)card
               hostConfig:(ACOHostConfig *)config;
@end
