//
//  ACOBaseCardElement
//  ACOBaseCardElement.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACOParseContext.h"

@interface ACOBaseCardElement:NSObject

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

@property ACRCardElementType type;

@end

@protocol ACOIBaseCardElementParser

- (ACOBaseCardElement *)deserialize:(NSData *)json parseContext:(ACOParseContext* )parseContext;

@end
