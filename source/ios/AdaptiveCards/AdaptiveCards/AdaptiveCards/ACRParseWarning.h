//
//  ACRParseWarning
//  ACRParseWarning.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, ACRParseWarningStatusCode) {
    ACRUnknownElementType = 0,
    ACRUnknownPropertyOnElement,
    ACRUnknownEnumValue,
    ACRNoRendererForType,
    ACRInteractivityNotSupported,
    ACRMaxActionsExceeded,
    ACRAssetLoadFailed,
    ACRUnsupportedSchemaVersion,
};

@interface ACRParseWarning : NSObject

@property (readonly) ACRParseWarningStatusCode statusCode;
@property (readonly) NSString *reason;

@end
