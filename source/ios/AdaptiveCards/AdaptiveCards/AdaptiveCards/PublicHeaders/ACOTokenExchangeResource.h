//
//  ACOTokenExchangeResource
//  ACOTokenExchangeResource.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ACOTokenExchangeResource : NSObject

@property NSString *Id;
@property NSString *uri;
@property NSString *providerId;

- (instancetype)init:(NSString *)stringId uri:(NSString *)uri providerId:(NSString *)providerId;

@end
