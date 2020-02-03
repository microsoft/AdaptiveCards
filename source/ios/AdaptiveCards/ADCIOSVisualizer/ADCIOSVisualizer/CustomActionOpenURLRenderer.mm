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

- (UIButton *)renderButton:(ACRView *)rootView
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig;
{
    ACRActionOpenURLRenderer *defaultRenderer = [ACRActionOpenURLRenderer getInstance];

    UIButton *button = [defaultRenderer renderButton:rootView
                                              inputs:inputs
                                           superview:superview
                                   baseActionElement:acoElem
                                          hostConfig:acoConfig];
    NSString *userSpecifiedBackgroundColor = nil;
    if (button) {
        NSData *additionalProperty = [acoElem additionalProperty];
        if (additionalProperty) {
            NSDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:additionalProperty options:NSJSONReadingMutableLeaves error:nil];
            userSpecifiedBackgroundColor = dictionary[@"color"];
        }
        UIColor *backgroundColor = nil;
        if (userSpecifiedBackgroundColor) {
            if ([userSpecifiedBackgroundColor isEqualToString:@"green"]) {
                backgroundColor = [UIColor colorWithRed:76.0 / 255.0
                                                  green:217.0 / 255.0
                                                   blue:100.0 / 255.0
                                                  alpha:1.0];
            }
        }
        if (!backgroundColor) {
            backgroundColor = [UIColor colorWithRed:1.0
                                              green:59.0 / 255.0
                                               blue:48.0 / 255.0
                                              alpha:1.0];
        }
        [button setBackgroundColor:backgroundColor];
    }
    return button;
}
@end
