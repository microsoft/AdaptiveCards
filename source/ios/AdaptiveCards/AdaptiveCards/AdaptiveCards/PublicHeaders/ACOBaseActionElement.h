//
//  ACOBaseActionElement
//  ACOBaseActionElement.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOEnums.h"
#import "ACOParseContext.h"
#import <Foundation/Foundation.h>

@class ACOFeatureRegistration;

@interface ACOBaseActionElement : NSObject

@property ACRActionType type;
@property NSString *sentiment;
@property (nonatomic, copy) NSString *tooltip;
@property (nonatomic, readonly) NSString *inlineTooltip;

- (NSString *)title;
- (NSString *)elementId;
- (NSString *)url;
- (NSString *)data;
- (NSString *)verb;
- (NSData *)additionalProperty;
- (BOOL)isEnabled;
- (BOOL)meetsRequirements:(ACOFeatureRegistration *)featureReg;

+ (NSNumber *)getKey:(ACRActionType)actionType;

@end

@protocol ACOIBaseActionElementParser

- (ACOBaseActionElement *)deserialize:(NSData *)json parseContext:(ACOParseContext *)parseContext;

@end
