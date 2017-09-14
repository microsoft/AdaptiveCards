//
//  ACRHostConfig.mm
//  ACRHostConfig.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACRHostConfig.h"
#import "ACRHostConfigInternal.h"

@implementation ACRHostConfig

- (instancetype)init
{
    self = [super init];
    return self;
}

- (ACRHostConfig *)fromJson:(NSString *)payload;
{
    ACRHostConfig *config = [[ACRHostConfigInternal alloc] init];

    if(config)
    {
        return [config fromJson:payload];
    }

    return nil;
}

@end
