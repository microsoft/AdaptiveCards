//
//  Util
//  Util.mm
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "Util.h"
#import "ACRContentStackView.h"
#import "ACOHostConfigPrivate.h"

using namespace AdaptiveCards;

void configVisibility(UIView *view, std::shared_ptr<BaseCardElement> const &visibilityInfo)
{
    view.hidden = !(visibilityInfo->GetIsVisible());
    NSString *hashkey = [NSString stringWithCString:visibilityInfo->GetId().c_str() encoding:NSUTF8StringEncoding];
    view.tag = hashkey.hash;
}

void configBleed(ACRView *rootView, std::shared_ptr<BaseCardElement> const &elem, ACRContentStackView *container, ACOHostConfig *acoConfig)
{
    std::shared_ptr<CollectionTypeElement> collection = std::dynamic_pointer_cast<CollectionTypeElement>(elem);
    if (collection) {
        // check current collection type element has padding, if so added to the padding map
        [rootView updatePaddingMap:collection view:container];
        // bleed specification requires the object that's asked to be bled to have padding
        if (collection->GetPadding()) {
            std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
            // bleed specification requires that there should be at leat one parental object with padding
            if (collection->GetCanBleed()) {
                InternalId internalId = collection->GetParentalId();
                ACRContentStackView *view = (ACRContentStackView *)[rootView getBleedTarget:internalId];
                // c++ to object-c enum conversion
                if (view) {

                    ACRBleedDirection direction = ACRRestricted;
                    switch (collection->GetBleedDirection()) {
                        case ContainerBleedDirection::BleedToLeading:
                            direction = ACRToLeadingEdge;
                            break;
                        case ContainerBleedDirection::BleedToTrailing:
                            direction = ACRToTrailingEdge;
                            break;
                        case ContainerBleedDirection::BleedToBothEdges:
                            direction = ACRToBothEdges;
                            break;
                        default:
                            direction = ACRRestricted;
                            break;
                    }
                    // creates background view (bv).
                    // the view is added to a view that is bleed target and parent view (tv).
                    // bv is then expanded to the tv according to bleed direction
                    // bv gets current container view's (cv) container style
                    // and cv's container style is rest, such that
                    // bv's container style will see through
                    // then we have two views, containers's stack view (csv) than holds content views, and bv that dislpays container style
                    // we transpose them, and get the final result
                    UIView *backgroundView = [[UIView alloc] init];
                    backgroundView.translatesAutoresizingMaskIntoConstraints = NO;
                    [view addSubview:backgroundView];
                    backgroundView.backgroundColor = container.backgroundColor;
                    container.backgroundColor = NULL;
                    [backgroundView.topAnchor constraintEqualToAnchor:container.topAnchor].active = YES;
                    [backgroundView.bottomAnchor constraintEqualToAnchor:container.bottomAnchor].active = YES;

                    // resets current width constraints and update them with new one according to bleed specification
                    [container bleed:config->GetSpacing().paddingSpacing priority:1000 target:backgroundView
                           direction:direction];
                    
                    if([container layer].borderWidth) {
                        [backgroundView layer].borderWidth = [container layer].borderWidth;
                        [container layer].borderWidth = 0;
                    }

                    if([container layer].borderColor) {
                        [backgroundView layer].borderColor = [container layer].borderColor;
                        [container layer].borderColor = 0;
                    }

                    if (direction == ACRToLeadingEdge || direction == ACRToBothEdges) {
                        [backgroundView.leadingAnchor constraintEqualToAnchor:view.leadingAnchor].active = YES;

                        if (direction == ACRToLeadingEdge) {
                            [backgroundView.trailingAnchor constraintEqualToAnchor:container.trailingAnchor].active = YES;
                        }
                    }

                    if (direction == ACRToTrailingEdge || direction == ACRToBothEdges) {
                        [backgroundView.trailingAnchor constraintEqualToAnchor:view.trailingAnchor].active = YES;
                        if (direction == ACRToTrailingEdge) {
                            [backgroundView.leadingAnchor constraintEqualToAnchor:container.leadingAnchor].active = YES;
                        }
                    }
                    
                    if (direction != ACRRestricted) {
                        [container.stackView.centerXAnchor constraintEqualToAnchor:backgroundView.centerXAnchor].active = YES;
                    }
                }
            }
        }
    }
}
