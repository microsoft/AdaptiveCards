//
//  ACOResourceResolvers.mm
//  ACOResourceResolvers.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACOResourceResolvers.h"

@implementation ACOResourceResolvers
{
    NSMutableDictionary<NSString *, NSObject<ACOIResourceResolver> *> *_resolvers;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        _resolvers = [[NSMutableDictionary alloc] init];
    }
    return self;
}

- (void)setResourceResolver:(NSObject<ACOIResourceResolver> *)resolver scheme:(NSString *)scheme
{
    self->_resolvers[scheme] = resolver;
}

- (NSObject<ACOIResourceResolver> *)getResourceResolverForScheme:(NSString *)scheme
{
    return self->_resolvers[scheme];
}

@end
