//
//  ACRHostConfig.h
//  ACRHostConfig
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOHostConfigParseResult.h"
#import "ACOResourceResolvers.h"

@interface ACOHostConfig:NSObject

@property BOOL allActionsHaveIcons;
@property CGFloat buttonPadding;
@property ACOResourceResolvers *resolvers;
@property NSURL *baseURL;

- (instancetype)init;

- (NSObject<ACOIResourceResolver> *)getResourceResolverForScheme:(NSString *)scheme;

+ (ACOHostConfigParseResult *)fromJson:(NSString *)payload;

+ (ACOHostConfigParseResult *)fromJson:(NSString *)payload resourceResolvers:(ACOResourceResolvers *)resolvers;

@end
