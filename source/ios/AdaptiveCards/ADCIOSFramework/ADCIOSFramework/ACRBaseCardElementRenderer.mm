//
//  ACRBaseCardElementRenderer
//  ACRBaseCardElementRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseCardElementRenderer.h"

@implementation ACRBaseCardElementRenderer

- (void) setSeparationConfig: (UIView* ) viewGroup{
            //SeparationStyle separationStyle,
            //SeparationConfig defaultSeparationConfig,
            //SeparationConfig strongSeparationConfig,
            //(Boolean) horizontalLine)
}

- (UIView* ) render: (UIView*) viewGroup
       withCardElem: (std::shared_ptr<BaseCardElement> const &) elem
       andHostCofig: (std::shared_ptr<HostConfig> const&) config
       { 
           return viewGroup;
       }

@end
