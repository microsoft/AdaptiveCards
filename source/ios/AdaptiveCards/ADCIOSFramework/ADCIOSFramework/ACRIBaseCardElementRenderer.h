//
//  ACRIBaseCardElementRenderer
//  ACRIBaseCardElementRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#include "BaseCardElement.h"
#include "HostConfig.h"

using namespace AdaptiveCards;

@protocol ACRIBaseCardElementRenderer

+ (CardElementType) elemType;

- (UIView* ) render: (UIStackView*) viewGroup
       withCardElem: (std::shared_ptr<BaseCardElement> const &) elem
      andHostConfig: (std::shared_ptr<HostConfig> const &) config;
@end
