//
//  CustomActionOpenURLRenderer
//  CustomActionOpenURLRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "CustomActionOpenURLRenderer.h"

@implementation CustomActionOpenURLRenderer

+ (CustomActionOpenURLRenderer *)getInstance
{
    static CustomActionOpenURLRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIButton* )renderButton:(UIViewController *)vc
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig;
{
    ACRActionOpenURLRenderer *defaultRenderer = [ACRActionOpenURLRenderer getInstance];

    UIButton *button = [defaultRenderer renderButton:vc
                                                inputs:inputs
                                             superview:superview
                                     baseActionElement:acoElem
                                            hostConfig:acoConfig];
    if(button)
    {
        [button setBackgroundColor:[UIColor colorWithRed:1.0
                                                   green:59.0/255.0
                                                    blue:48.0/255.0
                                                   alpha:1.0]];
    }
    return button;
}
@end
