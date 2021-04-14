//
//  ACOBaseActionElement
//  ACOBaseActionElement.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOParseContext.h"
#import "ACOEnums.h"
#import <Foundation/Foundation.h>

@class ACOFeatureRegistration;

@interface ACOBaseActionElement : NSObject

@property ACRActionType type;
@property NSString *sentiment;

- (NSString *)title;
- (NSString *)elementId;
- (NSString *)url;
- (NSString *)data;
- (NSString *)verb;
- (NSData *)additionalProperty;

- (BOOL)meetsRequirements:(ACOFeatureRegistration *)featureReg;

+ (NSNumber *)getKey:(ACRActionType)actionType;

@end

@protocol ACOIBaseActionElementParser

- (ACOBaseActionElement *)deserialize:(NSData *)json parseContext:(ACOParseContext *)parseContext;

@end
