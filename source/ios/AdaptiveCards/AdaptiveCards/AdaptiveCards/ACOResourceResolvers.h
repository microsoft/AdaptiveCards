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

- (instancetype)init;
- (NSObject<ACOIResourceResolver> *)getResourceResolverForScheme:(NSString *)scheme;
- (void)setResourceResolver:(NSObject<ACOIResourceResolver> *)resolver scheme:(NSString *)scheme;

@end    
