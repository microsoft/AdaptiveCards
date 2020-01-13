//
//  ACREnums.h
//  AdaptiveCards
//
//  Created by Inyoung Woo on 1/13/20.
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, ACRWarningStatusCode) {
    ACRUnknownElementType = 0,
    ACRUnknownActionElementType,
    ACRUnknownPropertyOnElement,
    ACRUnknownEnumValue,
    ACRNoRendererForType,
    ACRInteractivityNotSupported,
    ACRMaxActionsExceeded,
    ACRAssetLoadFailed,
    ACRUnsupportedSchemaVersion,
    ACRUnsupportedMediaType,
    ACRInvalidMediaMix,
    ACRInvalidColorFormat,
    ACRInvalidDimensionSpecified,
    ACRInvalidLanguage,
    ACRInvalidValue,
    ACRCustomWarning,
};
