//
//  ACRRenderResult.mm
//  ACRRenderResult.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACRRenderResult.h"

@implementation ACRRenderResult

- (instancetype)init
{
    self = [super init];
    if(self)
    {
        self.succeeded= NO;
        self.viewcontroller = nil;
    }
    return self;
}

@end
