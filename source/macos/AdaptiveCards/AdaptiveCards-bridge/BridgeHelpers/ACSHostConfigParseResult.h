#ifndef ACSHostConfigParseResult_h
#define ACSHostConfigParseResult_h
#import <Foundation/Foundation.h>

#import "ACSHostConfig.h"

@interface ACSHostConfigParseResult : NSObject
@property (readonly) ACSHostConfig* _Nullable config;
@property (readonly) BOOL isValid;
@property (readonly) NSError* _Nullable error;

- (instancetype _Nonnull)initWithConfig:(ACSHostConfig * _Nullable)config error:(NSError * _Nullable)error;
@end

#endif
