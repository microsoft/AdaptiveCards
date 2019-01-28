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
    ACREmphasis
};

@property ACRCardElementType type;

@end

@protocol ACOIBaseCardElementParser

@optional
- (UIView *)deserializeToCustomUIElement:(NSData* )json;

@end
