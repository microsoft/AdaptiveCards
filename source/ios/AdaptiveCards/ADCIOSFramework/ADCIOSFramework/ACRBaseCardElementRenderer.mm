//
//  ACRBaseCardElementRenderer
//  ACRBaseCardElementRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseCardElementRenderer.h"

@implementation ACRBaseCardElementRenderer

+ (CardElementType) elemType
{
    return CardElementType::Unsupported;
}

/* not implemented ATM */
- (void) setSeparationConfig: (UIView* ) viewGroup
{
            //SeparationStyle separationStyle,
            //SeparationConfig defaultSeparationConfig,
            //SeparationConfig strongSeparationConfig,
            //(Boolean) horizontalLine)
}

- (UIView* ) render: (UIStackView*) viewGroup
       withCardElem: (std::shared_ptr<BaseCardElement> const &) elem
      andHostConfig: (std::shared_ptr<HostConfig> const&) config
{ 
   return viewGroup;
}

@end
