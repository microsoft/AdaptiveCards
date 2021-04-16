// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"

#import "ACSInputsConfigConvertor.h"
#import "ACSErrorMessageConfigConvertor.h"
#import "ACSLabelConfigConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSInputsConfigConvertor 

+(ACSInputsConfig *) convertCpp:(const AdaptiveCards::InputsConfig& )inputsConfigCpp
{ 
     @autoreleasepool { 
 
        ACSInputsConfig*  inputsConfigCocoa = [[ ACSInputsConfig  alloc] initWithLabel: [ACSLabelConfigConvertor convertCpp:inputsConfigCpp.label] 
        errorMessage: [ACSErrorMessageConfigConvertor convertCpp:inputsConfigCpp.errorMessage]];
        return  inputsConfigCocoa;
   }
}

+(AdaptiveCards::InputsConfig) convertObj:(ACSInputsConfig *)inputsConfigObjc {
  AdaptiveCards::InputsConfig inputsConfigCpp;
  inputsConfigCpp.label = [ACSLabelConfigConvertor convertObj:inputsConfigObjc.label];
  inputsConfigCpp.errorMessage = [ACSErrorMessageConfigConvertor convertObj:inputsConfigObjc.errorMessage];
  return  inputsConfigCpp;
}

@end 
