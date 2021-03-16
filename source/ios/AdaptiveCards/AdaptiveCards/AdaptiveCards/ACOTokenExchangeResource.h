//
//  ACOTokenExchangeResource
//  ACOTokenExchangeResource.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ACOTokenExchangeResource : NSObject

@property NSString *id;
@property NSString *uri;
@property NSString *providerId;

- (instancetype)init:(NSString *)id uri:(NSString *)uri providerId:(NSString *)providerId;

@end
