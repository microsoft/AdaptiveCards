//
//  ACRIBaseCardElementRenderer
//  ACRIBaseCardElementRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
//

#import "ACOHostConfig.h"
#import "ACRContentStackView.h"
#import "ACRView.h"
#import <UIKit/UIKit.h>

@protocol ACRIBaseCardElementRenderer

+ (ACRCardElementType)elemType;

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
@optional
/// override this method for custom styling
/// not all renderers supports it
- (void)configure:(UIView *)view
           rootView:(ACRView *)rootView
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;

- (void)configureVC:(UIViewController *)view
           rootView:(ACRView *)rootView
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
@end

@protocol ACRIKVONotificationHandler

- (void)configUpdateForUIImageView:(ACRView *)rootView acoElem:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image imageView:(UIImageView *)imageView;
@end
