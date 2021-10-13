//
//  ACOBundle
//  ACOBundle.m
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOBundle.h"
#import "ACRView.h"

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
        NSBundle *bundle = [NSBundle bundleForClass:[ACRView class]];
        if (bundle) {
            NSURL *url = [bundle URLForResource:@"AdaptiveCards" withExtension:@"bundle"];
            if (url) {
                self->_bundle = [NSBundle bundleWithURL:url];
            } else {
                self->_bundle = bundle;
            }
        }
#endif
    }
    return self;
}

- (NSBundle *)getBundle
{
    return _bundle;
}


@end
