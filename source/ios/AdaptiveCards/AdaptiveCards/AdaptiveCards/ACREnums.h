//
//  ACREnums.h
//  AdaptiveCards
//
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
    ACRMissingInputErrorMessage,
    ACRCustomWarning,
};

typedef NS_ENUM(NSUInteger, ACRImageSize) {
    ACRImageSizeNone = 0,
    ACRImageSizeAuto,
    ACRImageSizeStretch,
    ACRImageSizeExplicit,
    ACRImageSizeSmall,
    ACRImageSizeMedium,
    ACRImageSizeLarge
};
