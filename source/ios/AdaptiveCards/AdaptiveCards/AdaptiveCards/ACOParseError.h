//
//  ACOParseError.h
//  ACOParseError
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ACOParseError:NSObject
@property NSString *errorMessage;
@property NSNumber *errorCode;
- (instancetype)init:(NSString *)errorMessage errorCode:(NSNumber *)errorCode;
@end    
