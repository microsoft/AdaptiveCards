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
    NSMutableDictionary<NSString *, ImageLoadBlock> *_resolvers;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        _resolvers = [[NSMutableDictionary alloc] init];
    }
    return self;
}

- (void)setResolverBlock:(ImageLoadBlock)resolver scheme:(NSString *)scheme
{
    dispatch_sync(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        self->_resolvers[scheme] = resolver;
    });
}

- (ImageLoadBlock)getResolverBlockForScheme:(NSString *)scheme
{
    __block ImageLoadBlock blockToReturn = nil;
    dispatch_sync(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        blockToReturn = self->_resolvers[scheme];
    });
    return blockToReturn;
}

@end
