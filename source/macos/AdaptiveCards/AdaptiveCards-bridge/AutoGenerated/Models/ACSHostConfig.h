// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSHostConfig_IMPORTED
#define ACSHostConfig_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
//#import "HostConfig.h"
using namespace AdaptiveCards;
#endif

#import "ACSContainerStyle.h"
//#import "ACSContainerStyleDefinition.h"
//#import "ACSContainerStylesDefinition.h"
//#import "ACSFactSetConfig.h"
//#import "ACSFontSizesConfig.h"
#import "ACSFontType.h"
//#import "ACSFontTypeDefinition.h"
//#import "ACSFontTypesDefinition.h"
#import "ACSFontWeightsConfig.h"
#import "ACSForegroundColor.h"
//#import "ACSImageConfig.h"
//#import "ACSImageSetConfig.h"
//#import "ACSImageSizesConfig.h"
//#import "ACSInputsConfig.h"
//#import "ACSMediaConfig.h"
//#import "ACSSeparatorConfig.h"
//#import "ACSSpacingConfig.h"
#import "ACSTextSize.h"
#import "ACSTextWeight.h"



  

@class ACSActionsConfig;
@class ACSAdaptiveCardConfig;
@class ACSColorConfig;
@class ACSColorsConfig;
@class ACSContainerStyleDefinition;
@class ACSContainerStylesDefinition;
@class ACSFactSetConfig;
@class ACSFontSizesConfig;
@class ACSFontTypeDefinition;
@class ACSFontTypesDefinition;
@class ACSFontWeightsConfig;
@class ACSImageConfig;
@class ACSImageSetConfig;
@class ACSImageSizesConfig;
@class ACSInputsConfig;
@class ACSMediaConfig;
@class ACSSeparatorConfig;
@class ACSSpacingConfig;

enum ACSContainerStyle: NSUInteger;
enum ACSFontType: NSUInteger;
enum ACSForegroundColor: NSUInteger;
enum ACSTextSize: NSUInteger;
enum ACSTextWeight: NSUInteger;


@interface ACSHostConfig : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithHostConfig:(const std::shared_ptr<HostConfig>)cppObj;
#endif

- (ACSFontTypeDefinition * _Nullable)getFontType:(enum ACSFontType)fontType;
- (NSString * _Nullable)getFontFamily:(enum ACSFontType)fontType;
- (NSNumber * _Nullable)getFontSize:(enum ACSFontType)fontType size:(enum ACSTextSize)size;
- (NSNumber * _Nullable)getFontWeight:(enum ACSFontType)fontType weight:(enum ACSTextWeight)weight;
- (NSString * _Nullable)getBackgroundColor:(enum ACSContainerStyle)style;
- (NSString * _Nullable)getForegroundColor:(enum ACSContainerStyle)style color:(enum ACSForegroundColor)color isSubtle:(bool)isSubtle;
- (NSString * _Nullable)getHighlightColor:(enum ACSContainerStyle)style color:(enum ACSForegroundColor)color isSubtle:(bool)isSubtle;
- (NSString * _Nullable)getBorderColor:(enum ACSContainerStyle)style;
- (NSNumber * _Nullable)getBorderThickness:(enum ACSContainerStyle)style;
- (NSString * _Nullable)getFontFamily;
- (void)setFontFamily:(NSString * _Nonnull)value;
- (ACSFontSizesConfig * _Nullable)getFontSizes;
- (void)setFontSizes:(ACSFontSizesConfig * _Nonnull)value;
- (ACSFontWeightsConfig * _Nullable)getFontWeights;
- (void)setFontWeights:(ACSFontWeightsConfig * _Nonnull)value;
- (ACSFontTypesDefinition * _Nullable)getFontTypes;
- (void)setFontTypes:(ACSFontTypesDefinition * _Nonnull)value;
- (bool)getSupportsInteractivity;
- (void)setSupportsInteractivity:(bool)value;
- (NSString * _Nullable)getImageBaseUrl;
- (void)setImageBaseUrl:(NSString * _Nonnull)value;
- (ACSImageSizesConfig * _Nullable)getImageSizes;
- (void)setImageSizes:(ACSImageSizesConfig * _Nonnull)value;
- (ACSImageConfig * _Nullable)getImage;
- (void)setImage:(ACSImageConfig * _Nonnull)value;
- (ACSSeparatorConfig * _Nullable)getSeparator;
- (void)setSeparator:(ACSSeparatorConfig * _Nonnull)value;
- (ACSSpacingConfig * _Nullable)getSpacing;
- (void)setSpacing:(ACSSpacingConfig * _Nonnull)value;
- (ACSAdaptiveCardConfig * _Nullable)getAdaptiveCard;
- (void)setAdaptiveCard:(ACSAdaptiveCardConfig * _Nonnull)value;
- (ACSImageSetConfig * _Nullable)getImageSet;
- (void)setImageSet:(ACSImageSetConfig * _Nonnull)value;
- (ACSFactSetConfig * _Nullable)getFactSet;
- (void)setFactSet:(ACSFactSetConfig * _Nonnull)value;
- (ACSActionsConfig * _Nullable)getActions;
- (void)setActions:(ACSActionsConfig * _Nonnull)value;
- (ACSContainerStylesDefinition * _Nullable)getContainerStyles;
- (void)setContainerStyles:(ACSContainerStylesDefinition * _Nonnull)value;
- (ACSMediaConfig * _Nullable)getMedia;
- (void)setMedia:(ACSMediaConfig * _Nonnull)value;
- (ACSInputsConfig * _Nullable)getInputs;
- (void)setInputs:(ACSInputsConfig * _Nonnull)value;


@end
#endif
