//
//  Util
//  Util.mm
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "Util.h"
#import "ACRContentStackView.h"

using namespace AdaptiveCards;

void configVisibility(UIView *view, std::shared_ptr<BaseCardElement> const &visibilityInfo)
{
    view.hidden = !(visibilityInfo->GetIsVisible());
    NSString *hashkey = [NSString stringWithCString:visibilityInfo->GetId().c_str() encoding:NSUTF8StringEncoding];
    view.tag = hashkey.hash;
}

void configBleed(ACRView *rootView, std::shared_ptr<BaseCardElement> const &elem, ACRContentStackView *container)
{
    std::shared_ptr<CollectionTypeElement> collection = std::dynamic_pointer_cast<CollectionTypeElement>(elem);
    if (collection) {

        [rootView updatePaddingMap:collection view:container];

        if (collection->GetCanBleed()) {
            InternalId internalId = collection->GetParentalId();
            ACRContentStackView *view = (ACRContentStackView *)[rootView getBleedTarget:internalId];
            if (view) {
                [container removeConstraints:container.widthconstraint];
                //[view removeConstraints:view.widthconstraint];
                [container.layoutMarginsGuide.leadingAnchor constraintEqualToAnchor:view.leadingAnchor].active = YES;
                [container.trailingAnchor constraintEqualToAnchor:view.trailingAnchor].active = YES;
            }
        }
    }
}
