//
//  ACOBundle
//  ACOBundle.m
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOBundle.h"

@implementation ACOBundle {
    NSBundle *_bundle;
}

+ (ACOBundle *)getInstance
{
    static ACOBundle *singletonInstance = nil;
    if (!singletonInstance) {
        singletonInstance = [[self alloc] init];
    }
    return singletonInstance;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
#ifdef SWIFT_PACKAGE
        self->_bundle = SWIFTPM_MODULE_BUNDLE;
#else
        self->_bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
#endif
    }
    return self;
}

- (NSBundle *)getBundle
{
    return _bundle;
}


@end
