//
//  ACRRegistartion
//  ACRRegistartion.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
//

#import "ACRBaseCardElementRenderer.h"

@interface ACRRegistration : NSObject 

+ (ACRRegistration* ) getInstance;

- (ACRBaseCardElementRenderer* ) getRenderer:(NSNumber* ) cardElementType;

- (UIView* ) render: (UIView*) view
      withCardElems: (std::vector<std::shared_ptr<BaseCardElement>> const &) elems
      andHostConfig: (std::shared_ptr<HostConfig> const &) config;

- (UIView* ) render: (UIView*) view
    withContentView: (UIView*) newView
      withCardElems: (std::vector<std::shared_ptr<BaseCardElement>> const &) elems
      andHostConfig: (std::shared_ptr<HostConfig> const &) config;
@end
