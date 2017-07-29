//
//  ACRRenderer
//  ACRRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SharedAdaptiveCard.h"
#import "HostConfig.h"

@interface ACRRenderer:NSObject

+ (UIView *)renderWithJson:(NSString *)str
            viewController:(UIViewController *)vc
                guideFrame:(CGRect)guideFrame
                hostconfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &)config;

+ (UIView *)renderWithAdaptiveCards:(std::shared_ptr<AdaptiveCards::AdaptiveCard> const &)adaptiveCard
                     viewController:(UIViewController *)vc
                         guideFrame:(CGRect)guideFrame
                         hostconfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &)config;
@end
