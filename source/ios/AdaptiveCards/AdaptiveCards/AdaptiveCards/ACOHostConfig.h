//
//  ACRHostConfig.h
//  ACRHostConfig
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOHostConfigParseResult.h"
#import "ACOResourceResolvers.h"
#import <Foundation/Foundation.h>

@interface ACOHostConfig : NSObject

@property CGFloat buttonPadding;
@property ACOResourceResolvers *resolvers;
@property NSURL *baseURL;

- (instancetype)init;

- (NSObject<ACOIResourceResolver> *)getResourceResolverForScheme:(NSString *)scheme;

- (ACOResolverIFType)getResolverIFType:(NSString *)scheme;

+ (ACOHostConfigParseResult *)fromJson:(NSString *)payload;

+ (ACOHostConfigParseResult *)fromJson:(NSString *)payload resourceResolvers:(ACOResourceResolvers *)resolvers;

- (NSNumber *)getIconPlacement:(NSNumber *)internalId;

@end
