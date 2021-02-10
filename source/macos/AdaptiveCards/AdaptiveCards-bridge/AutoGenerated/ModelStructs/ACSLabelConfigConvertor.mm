// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "../../../../../shared/cpp/ObjectModel/HostConfig.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"

#import "ACSLabelConfigConvertor.h"
#import "ACSInputLabelConfigConvertor.h"
#import "ACSSpacingConvertor.h"
#import "ACSSpacing.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSLabelConfigConvertor 

+(ACSLabelConfig *) convertCpp:(const AdaptiveCards::LabelConfig& )labelConfigCpp
{ 
     @autoreleasepool { 
 
        ACSLabelConfig*  labelConfigCocoa = [[ ACSLabelConfig  alloc] initWithInputSpacing: [ACSSpacingConvertor convertCpp:labelConfigCpp.inputSpacing] 
        requiredInputs: [ACSInputLabelConfigConvertor convertCpp:labelConfigCpp.requiredInputs]
        optionalInputs: [ACSInputLabelConfigConvertor convertCpp:labelConfigCpp.optionalInputs]];
        return  labelConfigCocoa;
   }
}

+(AdaptiveCards::LabelConfig) convertObj:(ACSLabelConfig *)labelConfigObjc {
  AdaptiveCards::LabelConfig labelConfigCpp;
  labelConfigCpp.inputSpacing = [ACSSpacingConvertor convertObj:labelConfigObjc.inputSpacing];
  labelConfigCpp.requiredInputs = [ACSInputLabelConfigConvertor convertObj:labelConfigObjc.requiredInputs];
  labelConfigCpp.optionalInputs = [ACSInputLabelConfigConvertor convertObj:labelConfigObjc.optionalInputs];
  return  labelConfigCpp;
}

@end 
