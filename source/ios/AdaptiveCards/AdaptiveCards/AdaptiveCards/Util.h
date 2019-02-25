//
//  Util.h
//  Util
//
//  Copyfight © 2019 Microsoft. All rights reserved.
//

#import<UIKit/UIKit.h>
#import "BaseCardElement.h"

using namespace AdaptiveCards;

void configVisibility(UIView *view, const std::shared_ptr<AdaptiveCards::BaseCardElement>visibilityInfo);

void renderBackgroundImage(const BackgroundImage *backgroundImageProperties, UIView *containerView, ACRView *rootView);

void applyBackgroundImageConstraints(const BackgroundImage *backgroundImageProperties, UIImageView *imageView, UIImage *img);
