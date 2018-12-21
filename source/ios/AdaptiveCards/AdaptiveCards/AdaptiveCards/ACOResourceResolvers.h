//
//  ACOResourceResolvers.h
//  ACOResourceResolvers
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACOIResourceResolver.h"

@interface ACOResourceResolvers:NSObject

typedef NS_ENUM(NSInteger, ACOResolverIFType) {
    ACODefaultIF = 0,
    ACOImageIF = 0,
    ACOImageViewIF,
};

- (instancetype)init;
- (ACOResolverIFType)getResolverIFType:(NSString *)scheme;
- (NSObject<ACOIResourceResolver> *)getResourceResolverForScheme:(NSString *)scheme;
- (void)setResourceResolver:(NSObject<ACOIResourceResolver> *)resolver scheme:(NSString *)scheme;

@end
