//
//  ACRBaseCardElementRenderer
//  ACRBaseCardElementRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseCardElementRenderer.h"

@implementation ACRBaseCardElementRenderer

+ (ACRCardElementType)elemType
{
    return ACRUnknown;
}

/* not implemented ATM */
- (void)setSeparationConfig:(UIView *)viewGroup
{
    //SeparationStyle separationStyle,
    //SeparationConfig defaultSeparationConfig,
    //SeparationConfig strongSeparationConfig,
    //(Boolean) horizontalLine)
}

- (UIView *)render:(UIStackView *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    return viewGroup;
}

+ (void)applyLayoutStyle:(NSString *)styleFormat viewsMap:(NSDictionary *)viewsMap
{
    NSArray<NSLayoutConstraint *> *constraints;

    for (NSString *key in viewsMap) {
        NSString *formatString = [[NSString alloc] initWithFormat:styleFormat, key];
        constraints = [NSLayoutConstraint constraintsWithVisualFormat:formatString
                                                              options:0
                                                              metrics:nil
                                                                views:viewsMap];
        [NSLayoutConstraint activateConstraints:constraints];
    }
}

@end
