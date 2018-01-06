//
//  ACRBaseCardElementRenderer
//  ACRBaseCardElementRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseCardElementRenderer.h"

@implementation ACRBaseCardElementRenderer

+ (CardElementType)elemType
{
    return CardElementType::Unsupported;
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
            rootViewController:(UIViewController *)vc
            inputs:(NSMutableArray *)inputs
      withCardElem:(std::shared_ptr<BaseCardElement> const &)elem
     andHostConfig:(std::shared_ptr<HostConfig> const&)config
{
   return viewGroup;
}

+ (void)applyLayoutStyle:(NSString *)styleFormat viewsMap:(NSDictionary *)viewsMap
{
    NSArray<NSLayoutConstraint *> *constraints;

    for(NSString *key in viewsMap)
    {
        NSString *formatString = [[NSString alloc] initWithFormat:styleFormat, key];
        constraints = [NSLayoutConstraint constraintsWithVisualFormat:formatString
                                                              options:0
                                                              metrics:nil
                                                                views:viewsMap];
        [NSLayoutConstraint activateConstraints:constraints];
    }
}

@end
