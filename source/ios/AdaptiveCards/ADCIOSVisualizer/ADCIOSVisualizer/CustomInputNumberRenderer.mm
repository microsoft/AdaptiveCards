//
//  CustomInputNumberRenderer
//  CustomInputNumberRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "CustomInputNumberRenderer.h"
#import <AdaptiveCards/ACFramework.h>

@implementation CustomInputNumberRenderer

+ (CustomInputNumberRenderer *)getInstance
{
    static CustomInputNumberRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
            rootViewController:(UIViewController *)vc
            inputs:(NSArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig
{
    ACRInputNumberRenderer *defaultRenderer = [ACRInputNumberRenderer getInstance];

    UIView *input = [defaultRenderer render:viewGroup
                         rootViewController:vc
                                     inputs:inputs
                            baseCardElement:acoElem
                                 hostConfig:acoConfig];
    if(input)
    {
        [input setBackgroundColor: [UIColor colorWithRed:1.0
                                                   green:59.0/255.0
                                                    blue:48.0/255.0
                                                   alpha:1.0]];
    }
    return input;
}
@end
