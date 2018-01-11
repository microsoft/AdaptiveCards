//
//  ACOParseResult.h
//  ACOParseResult
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ACOParseResult:NSObject

@property BOOL IsValid;
@property NSString *errorMessage;
@property NSNumber *errorCode

@end    
