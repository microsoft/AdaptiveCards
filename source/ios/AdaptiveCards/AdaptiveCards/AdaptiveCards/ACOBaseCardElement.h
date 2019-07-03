//
//  ACOBaseCardElement
//  ACOBaseCardElement.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOParseContext.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class ACOFeatureRegistration;

@interface ACOBaseCardElement : NSObject

- (NSData *)additionalProperty;

typedef NS_ENUM(NSInteger, ACRCardElementType) {
    // The order of enums must match with ones in enums.h
    ACRActionSet = 0,
    ACRAdaptiveCard,
    ACRChoiceInput,
    ACRChoiceSetInput,
    ACRColumn,
    ACRColumnSet,
    ACRContainer,
    ACRCustom,
    ACRDateInput,
    ACRFact,
    ACRFactSet,
    ACRImage,
    ACRImageSet,
    ACRMedia,
    ACRNumberInput,
    ACRRichTextBlock,
    ACRTextBlock,
    ACRTextInput,
    ACRTimeInput,
    ACRToggleInput,
    ACRUnknown
};

typedef NS_ENUM(NSInteger, ACRContainerStyle) {
    ACRNone,
    ACRDefault,
    ACREmphasis,
    ACRGood,
    ACRWarning,
    ACRAttention,
    ACRAccent
};

typedef NS_ENUM(NSInteger, ACRBleedDirection) {
    ACRBleedRestricted = 0x0000,
    ACRBleedToLeadingEdge = 0x0001,
    ACRBleedToTrailingEdge = 0x0010,
    ACRBleedToTopEdge = 0x0100,
    ACRBleedToBottomEdge = 0x1000,
    ACRBleedToAll = ACRBleedToLeadingEdge | ACRBleedToTrailingEdge | ACRBleedToTopEdge | ACRBleedToBottomEdge
};

@property ACRCardElementType type;

- (BOOL)meetsRequirements:(ACOFeatureRegistration *)featureReg;

@end

@protocol ACOIBaseCardElementParser

- (ACOBaseCardElement *)deserialize:(NSData *)json parseContext:(ACOParseContext *)parseContext;

@end
