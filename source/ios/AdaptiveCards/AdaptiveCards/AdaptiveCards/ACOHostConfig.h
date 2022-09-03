//
//  ACRHostConfig.h
//  ACRHostConfig
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACOHostConfigParseResult.h"
#import "ACOResourceResolvers.h"
#else
#import <AdaptiveCards/ACOHostConfigParseResult.h>
#import <AdaptiveCards/ACOResourceResolvers.h>
#endif
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
