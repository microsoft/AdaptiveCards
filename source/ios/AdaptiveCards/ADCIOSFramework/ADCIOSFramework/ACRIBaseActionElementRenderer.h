//
//  BaseActionElementRenderer
//  BaseActionElementRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "HostConfig.h"
#import "BaseActionElement.h"

using namespace AdaptiveCards;

@protocol ACRIBaseActionElementRenderer

- (UIButton* )renderButton:(UIViewController *)vc 
                 superview:(UIView *)superview
         baseActionElement:(std::shared_ptr<BaseActionElement> const &)elem
             andHostConfig:(std::shared_ptr<HostConfig> const &)config;
@end
