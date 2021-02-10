// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "../../../../../shared/cpp/ObjectModel/HostConfig.h"

#import "ACSContainerStylesDefinitionConvertor.h"
#import "ACSContainerStyleDefinitionConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSContainerStylesDefinitionConvertor 

+(ACSContainerStylesDefinition *) convertCpp:(const AdaptiveCards::ContainerStylesDefinition& )containerStylesDefinitionCpp
{ 
     @autoreleasepool { 
 
        ACSContainerStylesDefinition*  containerStylesDefinitionCocoa = [[ ACSContainerStylesDefinition  alloc] initWithDefaultPalette: [ACSContainerStyleDefinitionConvertor convertCpp:containerStylesDefinitionCpp.defaultPalette] 
        emphasisPalette: [ACSContainerStyleDefinitionConvertor convertCpp:containerStylesDefinitionCpp.emphasisPalette]
        goodPalette: [ACSContainerStyleDefinitionConvertor convertCpp:containerStylesDefinitionCpp.goodPalette]
        attentionPalette: [ACSContainerStyleDefinitionConvertor convertCpp:containerStylesDefinitionCpp.attentionPalette]
        warningPalette: [ACSContainerStyleDefinitionConvertor convertCpp:containerStylesDefinitionCpp.warningPalette]
        accentPalette: [ACSContainerStyleDefinitionConvertor convertCpp:containerStylesDefinitionCpp.accentPalette]];
        return  containerStylesDefinitionCocoa;
   }
}

+(AdaptiveCards::ContainerStylesDefinition) convertObj:(ACSContainerStylesDefinition *)containerStylesDefinitionObjc {
  AdaptiveCards::ContainerStylesDefinition containerStylesDefinitionCpp;
  containerStylesDefinitionCpp.defaultPalette = [ACSContainerStyleDefinitionConvertor convertObj:containerStylesDefinitionObjc.defaultPalette];
  containerStylesDefinitionCpp.emphasisPalette = [ACSContainerStyleDefinitionConvertor convertObj:containerStylesDefinitionObjc.emphasisPalette];
  containerStylesDefinitionCpp.goodPalette = [ACSContainerStyleDefinitionConvertor convertObj:containerStylesDefinitionObjc.goodPalette];
  containerStylesDefinitionCpp.attentionPalette = [ACSContainerStyleDefinitionConvertor convertObj:containerStylesDefinitionObjc.attentionPalette];
  containerStylesDefinitionCpp.warningPalette = [ACSContainerStyleDefinitionConvertor convertObj:containerStylesDefinitionObjc.warningPalette];
  containerStylesDefinitionCpp.accentPalette = [ACSContainerStyleDefinitionConvertor convertObj:containerStylesDefinitionObjc.accentPalette];
  return  containerStylesDefinitionCpp;
}

@end 
