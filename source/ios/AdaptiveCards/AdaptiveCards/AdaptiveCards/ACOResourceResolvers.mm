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
    dispatch_sync(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        self->_resolvers[scheme] = resolver;
    });
}

- (NSObject<ACOIResourceResolver> *)getResourceResolverForScheme:(NSString *)scheme
{
    __block NSObject<ACOIResourceResolver> *resolver = nil;
    dispatch_sync(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        resolver = self->_resolvers[scheme];
    });
    return resolver;
}

@end
