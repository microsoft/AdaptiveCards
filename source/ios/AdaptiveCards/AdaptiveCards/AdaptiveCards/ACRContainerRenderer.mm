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
#import "ACRLongPressGestureRecognizerFactory.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"

@implementation ACRContainerRenderer

+ (ACRContainerRenderer *)getInstance
{
    static ACRContainerRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRContainer;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
          rootView:(ACRView *)rootView
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<Container> containerElem = std::dynamic_pointer_cast<Container>(elem);

    ACRColumnView *container = [[ACRColumnView alloc] initWithStyle:(ACRContainerStyle)containerElem->GetStyle()
                                                        parentStyle:[viewGroup style] hostConfig:acoConfig];

    UIView *leadingBlankSpace = nil, *trailingBlankSpace = nil;
    if(containerElem->GetVerticalContentAlignment() == VerticalContentAlignment::Center || containerElem->GetVerticalContentAlignment() == VerticalContentAlignment::Bottom){
        leadingBlankSpace = [container addPaddingSpace];
    }
    
    container.frame = viewGroup.frame;

    [ACRRenderer render:container
               rootView:rootView
                 inputs:inputs
          withCardElems:containerElem->GetItems()
          andHostConfig:acoConfig];
    
    // Dont add the trailing space if the vertical content alignment is top/default
    if(containerElem->GetVerticalContentAlignment() == VerticalContentAlignment::Center || (containerElem->GetVerticalContentAlignment() == VerticalContentAlignment::Top && !(container.hasStretchableView))){
        trailingBlankSpace = [container addPaddingSpace];
    }
    
    [viewGroup addArrangedSubview:container];
        
    if(leadingBlankSpace != nil && trailingBlankSpace != nil){
        [NSLayoutConstraint constraintWithItem:leadingBlankSpace
                                     attribute:NSLayoutAttributeHeight
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:trailingBlankSpace
                                     attribute:NSLayoutAttributeHeight
                                    multiplier:1.0
                                      constant:0].active = YES;
    }

    std::shared_ptr<BaseActionElement> selectAction = containerElem->GetSelectAction();
    // instantiate and add tap gesture recognizer
    UILongPressGestureRecognizer * gestureRecognizer =
        [ACRLongPressGestureRecognizerFactory getLongPressGestureRecognizer:viewGroup
                                                                   rootView:rootView
                                                                 targetView:container
                                                              actionElement:selectAction
                                                                     inputs:inputs
                                                                 hostConfig:acoConfig];
    if(gestureRecognizer)
    {
        [container addGestureRecognizer:gestureRecognizer];
        container.userInteractionEnabled = YES;
    }
    return viewGroup;
}

@end

