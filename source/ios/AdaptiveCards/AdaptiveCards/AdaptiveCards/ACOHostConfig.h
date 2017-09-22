//
//  ACRHostConfig.h
//  ACRHostConfig
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOParseResult.h"

@interface ACOHostConfig:NSObject

- (instancetype)init;

+ (ACOParseResult *)fromJson:(NSString *)payload;
@end    
