//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "CustomActionSetRenderer.h"
#import <AdaptiveCards/ACOBaseActionElementPrivate.h>
#import <AdaptiveCards/ACRActionSetRenderer.h>

@implementation CustomActionSetRenderer

+ (CustomActionSetRenderer *)getInstance
{
    static CustomActionSetRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig
{
    UIView *containingView = [super render:viewGroup
                                  rootView:rootView
                                    inputs:(NSMutableArray *)inputs
                           baseCardElement:acoElem
                                hostConfig:acoConfig];
    // customize background color of action set
    containingView.backgroundColor = UIColor.darkGrayColor;
    return containingView;
}

@end
