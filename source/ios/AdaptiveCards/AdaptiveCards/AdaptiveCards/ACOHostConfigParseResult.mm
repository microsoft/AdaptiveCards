//
//  ACOHostConfigParseResult.mm
//  ACOHostConfigParseResult.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOHostConfigParseResult.h"

@implementation ACOHostConfigParseResult

- (instancetype)init
{
    self = [super init];
    if(self)
    {
        self.config = nil;
        self.IsValid = NO;
        self.parseErrors = [[NSMutableArray alloc] init];
    }
    return self;
}

@end
