//
//  ACRBaseActionElementRenderer
//  ACRBaseActionElementRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef USE_AC_SWIFT_PACKAGE
#import "ACRBaseActionElementRenderer.h"
#else
#import <AdaptiveCards/ACRBaseActionElementRenderer.h>
#endif

@implementation ACRBaseActionElementRenderer

- (UIButton *)renderButton:(UIViewController *)vc
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)config;
{
    return nil;
}

@end
