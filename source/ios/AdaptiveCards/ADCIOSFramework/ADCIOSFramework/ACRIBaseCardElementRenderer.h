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
#include "ACRContentStackView.h"

using namespace AdaptiveCards;

@protocol ACRIBaseCardElementRenderer

+ (CardElementType) elemType;

@optional
- (UIView* ) render: (UIView*) viewGroup
       withCardElem: (std::shared_ptr<BaseCardElement> const &) elem
      andHostConfig: (std::shared_ptr<HostConfig> const &) config;
// refactoring in progress; below method will eventually replace the above
@optional
- (UIView* ) renderX: (ACRContentStackView*) viewGroup
       withCardElem: (std::shared_ptr<BaseCardElement> const &) elem
      andHostConfig: (std::shared_ptr<HostConfig> const &) config;
@end
