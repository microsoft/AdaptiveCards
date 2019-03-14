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

        [rootView updatePaddingMap:collection view:container];

        if (collection->GetPadding()) {
            std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
            [container applyPadding:config->GetSpacing().paddingSpacing priority:1000];
            if (collection->GetCanBleed()) {
                InternalId internalId = collection->GetParentalId();
                ACRContentStackView *view = (ACRContentStackView *)[rootView getBleedTarget:internalId];
                if (view) {
                    auto direction = collection->GetBleedDirection();
                    if (direction == ContainerBleedDirection::BleedToLeading ||
                        direction == ContainerBleedDirection::BleedToBothEdges) {
                        [container.leadingAnchor constraintEqualToAnchor:view.leadingAnchor].active = YES;
                    }
                    
                    if (direction == ContainerBleedDirection::BleedToTrailing ||
                        direction == ContainerBleedDirection::BleedToBothEdges) {
                        [container.trailingAnchor constraintEqualToAnchor:view.trailingAnchor].active = YES;
                    }
                }
            }
        }
    }
}
