//
//  ACRContainerRenderer
//  ACRContainerRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRContainerRenderer.h"
#import "ACRRegistration.h"
#import "Container.h"
#import "SharedAdaptiveCard.h"

@implementation ACRContainerRenderer

+ (ACRContainerRenderer* ) getInstance
{
    static ACRContainerRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType) elemType
{
    return CardElementType::Container;
}

- (UIView* ) render: (UIStackView*) viewGroup
       withCardElem: (std::shared_ptr<BaseCardElement> const &) elem
      andHostConfig: (std::shared_ptr<HostConfig> const &) config
{
    std::shared_ptr<Container> containerElem = std::dynamic_pointer_cast<Container>(elem);
    return [[ACRRegistration getInstance] render: viewGroup
                                   withCardElems: containerElem->GetItems()
                                   andHostConfig: config];
}

@end

