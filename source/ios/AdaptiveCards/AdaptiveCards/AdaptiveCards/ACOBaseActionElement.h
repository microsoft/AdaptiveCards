//
//  ACOBaseActionElement
//  ACOBaseActionElement.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOParseContext.h"
#import <Foundation/Foundation.h>

@class ACOFeatureRegistration;

@interface ACOBaseActionElement : NSObject

typedef NS_ENUM(NSInteger, ACRActionType) {
    ACRShowCard = 1,
    ACRSubmit,
    ACROpenUrl,
    ACRToggleVisibility,
    ACRUnknownAction = 6,
};

typedef NS_ENUM(NSInteger, ACRIconPlacement) {
    ACRAboveTitle = 0,
    ACRLeftOfTitle,
    ACRNoTitle,
};

@property ACRActionType type;
@property NSString *sentiment;

- (NSString *)title;
- (NSString *)elementId;
- (NSString *)url;
- (NSString *)data;
- (NSData *)additionalProperty;

- (BOOL)meetsRequirements:(ACOFeatureRegistration *)featureReg;

@end

@protocol ACOIBaseActionElementParser

- (ACOBaseActionElement *)deserialize:(NSData *)json parseContext:(ACOParseContext *)parseContext;

@end
