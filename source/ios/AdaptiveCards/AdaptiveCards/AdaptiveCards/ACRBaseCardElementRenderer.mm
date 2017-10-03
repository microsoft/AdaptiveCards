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
            inputs:(NSMutableArray *)inputs
      withCardElem:(std::shared_ptr<BaseCardElement> const &)elem
     andHostConfig:(std::shared_ptr<HostConfig> const&)config
{
   return viewGroup;
}

+ (void)applyLayoutStyle:(NSString *)styleFormat view1:(UIView *)view1 view2:(UIView *)view2
{
    NSDictionary *dictionary = NSDictionaryOfVariableBindings(view1, view2);

    NSArray<NSLayoutConstraint *> *constraints;

    for(NSString *key in dictionary)
    {
        NSString *formatString = [[NSString alloc] initWithFormat:styleFormat, key];
        constraints = [NSLayoutConstraint constraintsWithVisualFormat:formatString
                                                              options:0
                                                              metrics:nil
                                                                views:dictionary];
        for(NSLayoutConstraint *constraint in constraints)
        {
            constraint.active = YES;
        }
    }
}

@end
