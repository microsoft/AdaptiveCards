//
//  ACRContainerRenderer
//  ACRContainerRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRContainerRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRColumnView.h"
#import "ACRRendererPrivate.h"
#import "ACRViewPrivate.h"
#import "Container.h"
#import "SharedAdaptiveCard.h"
#import "UtiliOS.h"

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

    [rootView.context pushBaseCardElementContext:acoElem];

    ACRColumnView *container = [[ACRColumnView alloc] initWithStyle:(ACRContainerStyle)containerElem->GetStyle()
                                                        parentStyle:[viewGroup style]
                                                         hostConfig:acoConfig
                                                          superview:viewGroup];
    container.rtl = rootView.context.rtl;

    [viewGroup addArrangedSubview:container];

    if (acoElem.type == ACRTableCell) {
        CGFloat top, left, bottom, right;
        top = left = bottom = right = [acoConfig getHostConfig]->GetSpacing().paddingSpacing;
        [container removeConstraints:container.constraints];
        [container applyPaddingToTop:top
                                left:left
                              bottom:bottom
                               right:right
                            priority:1000
                            location:ACRBleedToAll];
    } else {
        configBleed(rootView, elem, container, acoConfig);
    }

    renderBackgroundImage(containerElem->GetBackgroundImage(), container, rootView);

    UIView *leadingBlankSpace = nil, *trailingBlankSpace = nil;
    if (containerElem->GetVerticalContentAlignment() == VerticalContentAlignment::Center || containerElem->GetVerticalContentAlignment() == VerticalContentAlignment::Bottom) {
        leadingBlankSpace = [container addPaddingSpace];
    }

    container.frame = viewGroup.frame;

    [ACRRenderer render:container
               rootView:rootView
                 inputs:inputs
          withCardElems:containerElem->GetItems()
          andHostConfig:acoConfig];

    const VerticalContentAlignment adaptiveVAlignment = containerElem->GetVerticalContentAlignment().value_or(VerticalContentAlignment::Top);
    // Dont add the trailing space if the vertical content alignment is top/default
    if (adaptiveVAlignment == VerticalContentAlignment::Center || (adaptiveVAlignment == VerticalContentAlignment::Top && !(container.hasStretchableView))) {
        trailingBlankSpace = [container addPaddingSpace];
    }

    [container setClipsToBounds:NO];

    if (containerElem->GetMinHeight() > 0) {
        [NSLayoutConstraint constraintWithItem:container
                                     attribute:NSLayoutAttributeHeight
                                     relatedBy:NSLayoutRelationGreaterThanOrEqual
                                        toItem:nil
                                     attribute:NSLayoutAttributeNotAnAttribute
                                    multiplier:1
                                      constant:containerElem->GetMinHeight()]
            .active = YES;
    }

    if (leadingBlankSpace != nil && trailingBlankSpace != nil) {
        [NSLayoutConstraint constraintWithItem:leadingBlankSpace
                                     attribute:NSLayoutAttributeHeight
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:trailingBlankSpace
                                     attribute:NSLayoutAttributeHeight
                                    multiplier:1.0
                                      constant:0]
            .active = YES;
    }

    std::shared_ptr<BaseActionElement> selectAction = containerElem->GetSelectAction();
    ACOBaseActionElement *acoSelectAction = [ACOBaseActionElement getACOActionElementFromAdaptiveElement:selectAction];
    [container configureForSelectAction:acoSelectAction rootView:rootView];
    configVisibility(container, elem);

    [container hideIfSubviewsAreAllHidden];

    [rootView.context popBaseCardElementContext:acoElem];

    return viewGroup;
}

- (void)configUpdateForUIImageView:(ACRView *)rootView acoElem:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image imageView:(UIImageView *)imageView
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<Container> containerElem = std::dynamic_pointer_cast<Container>(elem);
    auto backgroundImageProperties = containerElem->GetBackgroundImage();

    renderBackgroundImage(rootView, backgroundImageProperties.get(), imageView, image);
}

@end
