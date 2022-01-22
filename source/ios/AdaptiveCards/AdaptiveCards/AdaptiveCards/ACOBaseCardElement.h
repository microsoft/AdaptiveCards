//
//  ACOBaseCardElement
//  ACOBaseCardElement.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOEnums.h"
#import "ACOParseContext.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class ACOFeatureRegistration;

@interface ACOBaseCardElement : NSObject

- (NSData *)additionalProperty;

@property ACRCardElementType type;

- (BOOL)meetsRequirements:(ACOFeatureRegistration *)featureReg;

@end

@protocol ACOIBaseCardElementParser

- (ACOBaseCardElement *)deserialize:(NSData *)json parseContext:(ACOParseContext *)parseContext;

@end
