// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"

#import "ACSContainerStyleDefinitionConvertor.h"
#import "ACSColorsConfigConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSContainerStyleDefinitionConvertor 

+(ACSContainerStyleDefinition *) convertCpp:(const AdaptiveCards::ContainerStyleDefinition& )containerStyleDefinitionCpp
{ 
     @autoreleasepool { 
 
        ACSContainerStyleDefinition*  containerStyleDefinitionCocoa = [[ ACSContainerStyleDefinition  alloc] initWithBackgroundColor: [NSString stringWithUTF8String:containerStyleDefinitionCpp.backgroundColor.c_str()] 
        borderColor: [NSString stringWithUTF8String:containerStyleDefinitionCpp.borderColor.c_str()]
        borderThickness: [NSNumber numberWithUnsignedInt:containerStyleDefinitionCpp.borderThickness]
        foregroundColors: [ACSColorsConfigConvertor convertCpp:containerStyleDefinitionCpp.foregroundColors]];
        return  containerStyleDefinitionCocoa;
   }
}

+(AdaptiveCards::ContainerStyleDefinition) convertObj:(ACSContainerStyleDefinition *)containerStyleDefinitionObjc {
  AdaptiveCards::ContainerStyleDefinition containerStyleDefinitionCpp;
  containerStyleDefinitionCpp.backgroundColor = std::string([containerStyleDefinitionObjc.backgroundColor UTF8String]);
  containerStyleDefinitionCpp.borderColor = std::string([containerStyleDefinitionObjc.borderColor UTF8String]);
  containerStyleDefinitionCpp.borderThickness = [containerStyleDefinitionObjc.borderThickness unsignedIntValue];
  containerStyleDefinitionCpp.foregroundColors = [ACSColorsConfigConvertor convertObj:containerStyleDefinitionObjc.foregroundColors];
  return  containerStyleDefinitionCpp;
}

@end 
