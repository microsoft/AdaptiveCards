//
//  ACOResourceResolvers.mm
//  ACOResourceResolvers.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import "ACOResourceResolvers.h"
#import <Foundation/Foundation.h>

@implementation ACOResourceResolvers {
    NSMutableDictionary<NSString *, NSObject<ACOIResourceResolver> *> *_resolvers;
    NSMutableDictionary<NSString *, NSNumber *> *_resolversIFMap;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        _resolvers = [[NSMutableDictionary alloc] init];
        _resolversIFMap = [[NSMutableDictionary alloc] init];
    }
    return self;
}

- (void)setResourceResolver:(NSObject<ACOIResourceResolver> *)resolver scheme:(NSString *)scheme
{
    self->_resolvers[scheme] = resolver;

    _resolversIFMap[scheme] = [NSNumber numberWithInt:ACODefaultIF];

    // only one IF per scheme is supported and ACRImageViewIF will be chosen
    // when both are implemented
    if ([resolver respondsToSelector:@selector(resolveImageViewResource:)]) {
        _resolversIFMap[scheme] = [NSNumber numberWithInt:ACOImageViewIF];
    } else if ([resolver respondsToSelector:@selector(resolveImageResource:)]) {
        _resolversIFMap[scheme] = [NSNumber numberWithInt:ACOImageIF];
    }
}

- (NSObject<ACOIResourceResolver> *)getResourceResolverForScheme:(NSString *)scheme
{
    return self->_resolvers[scheme];
}

- (ACOResolverIFType)getResolverIFType:(NSString *)scheme
{
    return (ACOResolverIFType)[_resolversIFMap[scheme] intValue];
}

@end
