//
//  ACOEnums
//  ACOEnums.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//
//
typedef NS_ENUM(NSInteger, ACRActionType) {
    ACRExecute = 1,
    ACROpenUrl,
    ACRShowCard,
    ACRSubmit,
    ACRToggleVisibility,
    ACROverflow,
    ACRUnknownAction = 7,
};

typedef NS_ENUM(NSInteger, ACRIconPlacement) {
    ACRAboveTitle = 0,
    ACRLeftOfTitle,
    ACRNoTitle,
};

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
    ACRTable,
    ACRTableCell,
    ACRTableRow,
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
    ACRAttention,
    ACRWarning,
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

typedef NS_ENUM(NSInteger, ACRRtl) {
    ACRRtlNone,
    ACRRtlRTL,
    ACRRtlLTR
};

typedef NS_ENUM(NSUInteger, ACRHorizontalAlignment) {
    ACRLeft = 0,
    ACRCenter,
    ACRRight
};


typedef NS_ENUM(NSUInteger, ACRVerticalContentAlignment) {
    ACRVerticalContentAlignmentTop = 0,
    ACRVerticalContentAlignmentCenter,
    ACRVerticalContentAlignmentBottom
};

typedef NS_ENUM(NSUInteger, ACRHeightType) {
    ACRHeightAuto = 0,
    ACRHeightStretch
};
