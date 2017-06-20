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

- (UIView* ) render: (UIView*) view
      withCardElems: (std::vector<std::shared_ptr<BaseCardElement>> const &) elems
      andHostConfig: (std::shared_ptr<HostConfig> const &) config;

- (ACRBaseCardElementRenderer* ) getRenderer:(NSString*) cardElementType;

@end
