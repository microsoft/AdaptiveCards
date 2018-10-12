//
//  ACOBaseCardElement
//  ACOBaseCardElement.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ACOBaseCardElement:NSObject

- (NSData *)additionalProperty;

typedef NS_ENUM(NSInteger, ACRCardElementType) {
    ACRUnsupported = 0,
    ACRAdaptiveCard,
    ACRTextBlock,
    ACRImage,
    ACRContainer,
    ACRColumn,
    ACRColumnSet,
    ACRFactSet,
    ACRFact,
    ACRImageSet,
    ACRChoiceInput,
    ACRChoiceSetInput,
    ACRDateInput,
    ACRNumberInput,
    ACRTextInput,
    ACRTimeInput,
    ACRToggleInput,
    ACRCustom,
    ACRUnknown,
    ACRMedia,
};

typedef NS_ENUM(NSInteger, ACRContainerStyle) {
    ACRNone,
    ACRDefault,
    ACREmphasis
};

@property ACRCardElementType type;

@end

@protocol ACOIBaseCardElementParser

@optional
- (UIView *)deserializeToCustomUIElement:(NSData* )json;

@end
