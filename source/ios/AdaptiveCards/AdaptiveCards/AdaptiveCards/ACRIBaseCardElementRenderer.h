//
//  ACRIBaseCardElementRenderer
//  ACRIBaseCardElementRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "ACRContentStackView.h"
#import "ACOHostConfig.h"
#import "ACOBaseCardElement.h"

using namespace AdaptiveCards;

@protocol ACRIBaseCardElementRenderer

+ (CardElementType)elemType;

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
            rootViewController:(UIViewController *)vc
            inputs:(NSArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
@end
