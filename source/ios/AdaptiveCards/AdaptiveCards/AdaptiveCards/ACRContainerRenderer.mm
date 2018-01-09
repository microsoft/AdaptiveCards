//
//  ACRContainerRenderer
//  ACRContainerRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRContainerRenderer.h"
#import "ACRColumnView.h"
#import "ACRRendererPrivate.h"
#import "Container.h"
#import "SharedAdaptiveCard.h"
#import "ACRTapGestureRecognizerFactory.h"

@implementation ACRContainerRenderer

+ (ACRContainerRenderer *)getInstance
{
    static ACRContainerRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::Container;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
rootViewController:(UIViewController *)vc
            inputs:(NSMutableArray *)inputs
      withCardElem:(std::shared_ptr<BaseCardElement> const &)elem
     andHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    std::shared_ptr<Container> containerElem = std::dynamic_pointer_cast<Container>(elem);

    ContainerStyle style = containerElem->GetStyle();

    if(style == ContainerStyle::None)
    {
        style = [viewGroup getStyle];
    }

    ACRColumnView *container = [[ACRColumnView alloc] initWithStyle:style hostConfig:config];

    [ACRRenderer render:container
     rootViewController:vc
                 inputs:inputs
          withCardElems:containerElem->GetItems()
          andHostConfig:config];
    [viewGroup addArrangedSubview:container];

    std::shared_ptr<BaseActionElement> selectAction = containerElem->GetSelectAction();
    // instantiate and add tap gesture recognizer
    UITapGestureRecognizer * tapGestureRecognizer =
        [ACRTapGestureRecognizerFactory getTapGestureRecognizer:viewGroup
                                             rootViewController:vc
                                                  actionElement:selectAction
                                                         inputs:inputs
                                                     hostConfig:config];
    if(tapGestureRecognizer)
    {
        [container addGestureRecognizer:tapGestureRecognizer];
        container.userInteractionEnabled = YES;
    }
    return viewGroup;
}

@end

