//
//  ACRHostConfig.h
//  ACRHostConfig
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ACRHostConfig:NSObject
- (instancetype)init;
// Helper for creating hostconfig objects
- (ACRHostConfig *)fromJson:(NSString *)payload;
@end    
