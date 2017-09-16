//
//  ACRHostConfig.mm
//  ACRHostConfig.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACOHostConfig.h"
#import "ACOHostConfigInternal.h"

@implementation ACOHostConfig

- (instancetype)init
{
    self = [super init];
    return self;
}

+ (ACOParseResult *)FromJson:(NSString *)payload;
{
    return [ACOHostConfigInternal FromJson:payload];
}

@end
