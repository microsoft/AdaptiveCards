//
//  Util.h
//  Util
//
//  Copyfight © 2019 Microsoft. All rights reserved.
//

#import<UIKit/UIKit.h>
#import "ACRViewPrivate.h"
#import "BaseCardElement.h"
#import "CollectionTypeElement.h"

using namespace AdaptiveCards;

void configVisibility(UIView *view, std::shared_ptr<AdaptiveCards::BaseCardElement> const &visibilityInfo);

void configBleed(ACRView *rootView, std::shared_ptr<BaseCardElement> const &elem, ACRContentStackView *container, ACOHostConfig *acoConfig);

void renderBackgroundImage(const std::shared_ptr<BackgroundImage> backgroundImageProperties, UIView *containerView, ACRView *rootView);

void renderBackgroundImage(const BackgroundImage *backgroundImageProperties, UIImageView *imageView, UIImage *img);

void applyBackgroundImageConstraints(const BackgroundImage *backgroundImageProperties, UIImageView *imageView, UIImage *img);

ObserverActionBlock generateBackgroundImageObserverAction(std::shared_ptr<BackgroundImage> backgroundImageProperties, ACRView *observer, std::shared_ptr<BaseCardElement> const &context);
