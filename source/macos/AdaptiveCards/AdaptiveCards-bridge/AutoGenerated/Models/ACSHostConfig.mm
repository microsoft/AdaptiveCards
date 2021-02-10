// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSActionsConfigConvertor.h"
#import "ACSAdaptiveCardConfigConvertor.h"
#import "ACSColorConfigConvertor.h"
#import "ACSColorsConfigConvertor.h"
#import "ACSContainerStyleConvertor.h"
#import "ACSContainerStyleDefinitionConvertor.h"
#import "ACSContainerStylesDefinitionConvertor.h"
#import "ACSFactSetConfigConvertor.h"
#import "ACSFontSizesConfig.h"
#import "ACSFontTypeConvertor.h"
#import "ACSFontTypeDefinitionConvertor.h"
#import "ACSFontTypesDefinitionConvertor.h"
#import "ACSFontWeightsConfig.h"
#import "ACSForegroundColorConvertor.h"
#import "ACSImageConfigConvertor.h"
#import "ACSImageSetConfigConvertor.h"
#import "ACSImageSizesConfigConvertor.h"
#import "ACSInputsConfigConvertor.h"
#import "ACSMediaConfigConvertor.h"
#import "ACSSeparatorConfigConvertor.h"
#import "ACSSpacingConfigConvertor.h"
#import "ACSTextSizeConvertor.h"
#import "ACSTextWeightConvertor.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/Enums.h"


#import "ACSHostConfig.h"
#import "../../../../../shared/cpp/ObjectModel/HostConfig.h"


@implementation  ACSHostConfig {
    std::shared_ptr<HostConfig> mCppObj;
}

- (instancetype _Nonnull)initWithHostConfig:(const std::shared_ptr<HostConfig>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (ACSFontTypeDefinition * _Nullable)getFontType:(enum ACSFontType)fontType
{
    auto fontTypeCpp = [ACSFontTypeConvertor convertObj:fontType];
 
    auto getFontTypeCpp = mCppObj->GetFontType(fontTypeCpp);
    return [ACSFontTypeDefinitionConvertor convertCpp:getFontTypeCpp];

}

- (NSString * _Nullable)getFontFamily:(enum ACSFontType)fontType
{
    auto fontTypeCpp = [ACSFontTypeConvertor convertObj:fontType];
 
    auto getFontFamilyCpp = mCppObj->GetFontFamily(fontTypeCpp);
    return [NSString stringWithUTF8String:getFontFamilyCpp.c_str()];

}

- (NSNumber * _Nullable)getFontSize:(enum ACSFontType)fontType size:(enum ACSTextSize)size
{
    auto fontTypeCpp = [ACSFontTypeConvertor convertObj:fontType];
    auto sizeCpp = [ACSTextSizeConvertor convertObj:size];
 
    auto getFontSizeCpp = mCppObj->GetFontSize(fontTypeCpp,sizeCpp);
    return [NSNumber numberWithUnsignedInt:getFontSizeCpp];

}

- (NSNumber * _Nullable)getFontWeight:(enum ACSFontType)fontType weight:(enum ACSTextWeight)weight
{
    auto fontTypeCpp = [ACSFontTypeConvertor convertObj:fontType];
    auto weightCpp = [ACSTextWeightConvertor convertObj:weight];
 
    auto getFontWeightCpp = mCppObj->GetFontWeight(fontTypeCpp,weightCpp);
    return [NSNumber numberWithUnsignedInt:getFontWeightCpp];

}

- (NSString * _Nullable)getBackgroundColor:(enum ACSContainerStyle)style
{
    auto styleCpp = [ACSContainerStyleConvertor convertObj:style];
 
    auto getBackgroundColorCpp = mCppObj->GetBackgroundColor(styleCpp);
    return [NSString stringWithUTF8String:getBackgroundColorCpp.c_str()];

}

- (NSString * _Nullable)getForegroundColor:(enum ACSContainerStyle)style color:(enum ACSForegroundColor)color isSubtle:(bool)isSubtle
{
    auto styleCpp = [ACSContainerStyleConvertor convertObj:style];
    auto colorCpp = [ACSForegroundColorConvertor convertObj:color];
    auto isSubtleCpp = isSubtle;
 
    auto getForegroundColorCpp = mCppObj->GetForegroundColor(styleCpp,colorCpp,isSubtleCpp);
    return [NSString stringWithUTF8String:getForegroundColorCpp.c_str()];

}

- (NSString * _Nullable)getHighlightColor:(enum ACSContainerStyle)style color:(enum ACSForegroundColor)color isSubtle:(bool)isSubtle
{
    auto styleCpp = [ACSContainerStyleConvertor convertObj:style];
    auto colorCpp = [ACSForegroundColorConvertor convertObj:color];
    auto isSubtleCpp = isSubtle;
 
    auto getHighlightColorCpp = mCppObj->GetHighlightColor(styleCpp,colorCpp,isSubtleCpp);
    return [NSString stringWithUTF8String:getHighlightColorCpp.c_str()];

}

- (NSString * _Nullable)getBorderColor:(enum ACSContainerStyle)style
{
    auto styleCpp = [ACSContainerStyleConvertor convertObj:style];
 
    auto getBorderColorCpp = mCppObj->GetBorderColor(styleCpp);
    return [NSString stringWithUTF8String:getBorderColorCpp.c_str()];

}

- (NSNumber * _Nullable)getBorderThickness:(enum ACSContainerStyle)style
{
    auto styleCpp = [ACSContainerStyleConvertor convertObj:style];
 
    auto getBorderThicknessCpp = mCppObj->GetBorderThickness(styleCpp);
    return [NSNumber numberWithUnsignedInt:getBorderThicknessCpp];

}

- (NSString * _Nullable)getFontFamily
{
 
    auto getFontFamilyCpp = mCppObj->GetFontFamily();
    return [NSString stringWithUTF8String:getFontFamilyCpp.c_str()];

}

- (void)setFontFamily:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetFontFamily(valueCpp);
    
}

- (ACSFontSizesConfig * _Nullable)getFontSizes
{
 
    auto getFontSizesCpp = mCppObj->GetFontSizes();
    return [[ACSFontSizesConfig alloc] init];

}

- (void)setFontSizes:(ACSFontSizesConfig * _Nonnull)value
{
//    auto valueCpp = // NEED TO INSERT CODE //;
//
//    mCppObj->SetFontSizes(valueCpp);
    
}

- (ACSFontWeightsConfig * _Nullable)getFontWeights
{
 
    auto getFontWeightsCpp = mCppObj->GetFontWeights();
    return [[ACSFontWeightsConfig alloc] init];

}

- (void)setFontWeights:(ACSFontWeightsConfig * _Nonnull)value
{
//    auto valueCpp = // NEED TO INSERT CODE //;
// 
//    mCppObj->SetFontWeights(valueCpp);
    
}

- (ACSFontTypesDefinition * _Nullable)getFontTypes
{
 
    auto getFontTypesCpp = mCppObj->GetFontTypes();
    return [ACSFontTypesDefinitionConvertor convertCpp:getFontTypesCpp];

}

- (void)setFontTypes:(ACSFontTypesDefinition * _Nonnull)value
{
    auto valueCpp = [ACSFontTypesDefinitionConvertor convertObj:value];
 
    mCppObj->SetFontTypes(valueCpp);
    
}

- (bool)getSupportsInteractivity
{
 
    auto getSupportsInteractivityCpp = mCppObj->GetSupportsInteractivity();
    return getSupportsInteractivityCpp;

}

- (void)setSupportsInteractivity:(bool)value
{
    auto valueCpp = value;
 
    mCppObj->SetSupportsInteractivity(valueCpp);
    
}

- (NSString * _Nullable)getImageBaseUrl
{
 
    auto getImageBaseUrlCpp = mCppObj->GetImageBaseUrl();
    return [NSString stringWithUTF8String:getImageBaseUrlCpp.c_str()];

}

- (void)setImageBaseUrl:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetImageBaseUrl(valueCpp);
    
}

- (ACSImageSizesConfig * _Nullable)getImageSizes
{
 
    auto getImageSizesCpp = mCppObj->GetImageSizes();
    return [ACSImageSizesConfigConvertor convertCpp:getImageSizesCpp];

}

- (void)setImageSizes:(ACSImageSizesConfig * _Nonnull)value
{
    auto valueCpp = [ACSImageSizesConfigConvertor convertObj:value];
 
    mCppObj->SetImageSizes(valueCpp);
    
}

- (ACSImageConfig * _Nullable)getImage
{
 
    auto getImageCpp = mCppObj->GetImage();
    return [ACSImageConfigConvertor convertCpp:getImageCpp];

}

- (void)setImage:(ACSImageConfig * _Nonnull)value
{
    auto valueCpp = [ACSImageConfigConvertor convertObj:value];
 
    mCppObj->SetImage(valueCpp);
    
}

- (ACSSeparatorConfig * _Nullable)getSeparator
{
 
    auto getSeparatorCpp = mCppObj->GetSeparator();
    return [ACSSeparatorConfigConvertor convertCpp:getSeparatorCpp];

}

- (void)setSeparator:(ACSSeparatorConfig * _Nonnull)value
{
    auto valueCpp = [ACSSeparatorConfigConvertor convertObj:value];
 
    mCppObj->SetSeparator(valueCpp);
    
}

- (ACSSpacingConfig * _Nullable)getSpacing
{
 
    auto getSpacingCpp = mCppObj->GetSpacing();
    return [ACSSpacingConfigConvertor convertCpp:getSpacingCpp];

}

- (void)setSpacing:(ACSSpacingConfig * _Nonnull)value
{
    auto valueCpp = [ACSSpacingConfigConvertor convertObj:value];
 
    mCppObj->SetSpacing(valueCpp);
    
}

- (ACSAdaptiveCardConfig * _Nullable)getAdaptiveCard
{
 
    auto getAdaptiveCardCpp = mCppObj->GetAdaptiveCard();
    return [ACSAdaptiveCardConfigConvertor convertCpp:getAdaptiveCardCpp];

}

- (void)setAdaptiveCard:(ACSAdaptiveCardConfig * _Nonnull)value
{
    auto valueCpp = [ACSAdaptiveCardConfigConvertor convertObj:value];
 
    mCppObj->SetAdaptiveCard(valueCpp);
    
}

- (ACSImageSetConfig * _Nullable)getImageSet
{
 
    auto getImageSetCpp = mCppObj->GetImageSet();
    return [ACSImageSetConfigConvertor convertCpp:getImageSetCpp];

}

- (void)setImageSet:(ACSImageSetConfig * _Nonnull)value
{
    auto valueCpp = [ACSImageSetConfigConvertor convertObj:value];
 
    mCppObj->SetImageSet(valueCpp);
    
}

- (ACSFactSetConfig * _Nullable)getFactSet
{
 
    auto getFactSetCpp = mCppObj->GetFactSet();
    return [ACSFactSetConfigConvertor convertCpp:getFactSetCpp];

}

- (void)setFactSet:(ACSFactSetConfig * _Nonnull)value
{
    auto valueCpp = [ACSFactSetConfigConvertor convertObj:value];
 
    mCppObj->SetFactSet(valueCpp);
    
}

- (ACSActionsConfig * _Nullable)getActions
{
 
    auto getActionsCpp = mCppObj->GetActions();
    return [ACSActionsConfigConvertor convertCpp:getActionsCpp];

}

- (void)setActions:(ACSActionsConfig * _Nonnull)value
{
    auto valueCpp = [ACSActionsConfigConvertor convertObj:value];
 
    mCppObj->SetActions(valueCpp);
    
}

- (ACSContainerStylesDefinition * _Nullable)getContainerStyles
{
 
    auto getContainerStylesCpp = mCppObj->GetContainerStyles();
    return [ACSContainerStylesDefinitionConvertor convertCpp:getContainerStylesCpp];

}

- (void)setContainerStyles:(ACSContainerStylesDefinition * _Nonnull)value
{
    auto valueCpp = [ACSContainerStylesDefinitionConvertor convertObj:value];
 
    mCppObj->SetContainerStyles(valueCpp);
    
}

- (ACSMediaConfig * _Nullable)getMedia
{
 
    auto getMediaCpp = mCppObj->GetMedia();
    return [ACSMediaConfigConvertor convertCpp:getMediaCpp];

}

- (void)setMedia:(ACSMediaConfig * _Nonnull)value
{
    auto valueCpp = [ACSMediaConfigConvertor convertObj:value];
 
    mCppObj->SetMedia(valueCpp);
    
}

- (ACSInputsConfig * _Nullable)getInputs
{
 
    auto getInputsCpp = mCppObj->GetInputs();
    return [ACSInputsConfigConvertor convertCpp:getInputsCpp];

}

- (void)setInputs:(ACSInputsConfig * _Nonnull)value
{
    auto valueCpp = [ACSInputsConfigConvertor convertObj:value];
 
    mCppObj->SetInputs(valueCpp);
    
}


@end
