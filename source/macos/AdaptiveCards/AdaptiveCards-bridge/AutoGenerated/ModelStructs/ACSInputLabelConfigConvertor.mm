// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"
#import "Enums.h"

#import "ACSInputLabelConfigConvertor.h"
#import "ACSForegroundColorConvertor.h"
#import "ACSTextSizeConvertor.h"
#import "ACSTextWeightConvertor.h"
#import "ACSForegroundColor.h"
#import "ACSTextSize.h"
#import "ACSTextWeight.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSInputLabelConfigConvertor 

+(ACSInputLabelConfig *) convertCpp:(const AdaptiveCards::InputLabelConfig& )inputLabelConfigCpp
{ 
     @autoreleasepool { 
 
        ACSInputLabelConfig*  inputLabelConfigCocoa = [[ ACSInputLabelConfig  alloc] initWithColor: [ACSForegroundColorConvertor convertCpp:inputLabelConfigCpp.color] 
        isSubtle: inputLabelConfigCpp.isSubtle
        size: [ACSTextSizeConvertor convertCpp:inputLabelConfigCpp.size]
        suffix: [NSString stringWithUTF8String:inputLabelConfigCpp.suffix.c_str()]
        weight: [ACSTextWeightConvertor convertCpp:inputLabelConfigCpp.weight]];
        return  inputLabelConfigCocoa;
   }
}

+(AdaptiveCards::InputLabelConfig) convertObj:(ACSInputLabelConfig *)inputLabelConfigObjc {
  AdaptiveCards::InputLabelConfig inputLabelConfigCpp;
  inputLabelConfigCpp.color = [ACSForegroundColorConvertor convertObj:inputLabelConfigObjc.color];
  inputLabelConfigCpp.isSubtle = inputLabelConfigObjc.isSubtle;
  inputLabelConfigCpp.size = [ACSTextSizeConvertor convertObj:inputLabelConfigObjc.size];
  inputLabelConfigCpp.suffix = std::string([inputLabelConfigObjc.suffix UTF8String]);
  inputLabelConfigCpp.weight = [ACSTextWeightConvertor convertObj:inputLabelConfigObjc.weight];
  return  inputLabelConfigCpp;
}

@end 
