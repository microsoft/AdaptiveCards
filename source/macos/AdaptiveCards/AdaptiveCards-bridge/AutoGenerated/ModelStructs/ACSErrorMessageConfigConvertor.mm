// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "../../../../../shared/cpp/ObjectModel/HostConfig.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"

#import "ACSErrorMessageConfigConvertor.h"
#import "ACSSpacingConvertor.h"
#import "ACSTextSizeConvertor.h"
#import "ACSTextWeightConvertor.h"
#import "ACSSpacing.h"
#import "ACSTextSize.h"
#import "ACSTextWeight.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSErrorMessageConfigConvertor 

+(ACSErrorMessageConfig *) convertCpp:(const AdaptiveCards::ErrorMessageConfig& )errorMessageConfigCpp
{ 
     @autoreleasepool { 
 
        ACSErrorMessageConfig*  errorMessageConfigCocoa = [[ ACSErrorMessageConfig  alloc] initWithSize: [ACSTextSizeConvertor convertCpp:errorMessageConfigCpp.size] 
        spacing: [ACSSpacingConvertor convertCpp:errorMessageConfigCpp.spacing]
        weight: [ACSTextWeightConvertor convertCpp:errorMessageConfigCpp.weight]];
        return  errorMessageConfigCocoa;
   }
}

+(AdaptiveCards::ErrorMessageConfig) convertObj:(ACSErrorMessageConfig *)errorMessageConfigObjc {
  AdaptiveCards::ErrorMessageConfig errorMessageConfigCpp;
  errorMessageConfigCpp.size = [ACSTextSizeConvertor convertObj:errorMessageConfigObjc.size];
  errorMessageConfigCpp.spacing = [ACSSpacingConvertor convertObj:errorMessageConfigObjc.spacing];
  errorMessageConfigCpp.weight = [ACSTextWeightConvertor convertObj:errorMessageConfigObjc.weight];
  return  errorMessageConfigCpp;
}

@end 
