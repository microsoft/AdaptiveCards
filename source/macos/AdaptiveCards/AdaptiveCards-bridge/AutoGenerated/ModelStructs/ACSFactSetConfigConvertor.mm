// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "../../../../../shared/cpp/ObjectModel/HostConfig.h"

#import "ACSFactSetConfigConvertor.h"
#import "ACSTextConfigConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSFactSetConfigConvertor 

+(ACSFactSetConfig *) convertCpp:(const AdaptiveCards::FactSetConfig& )factSetConfigCpp
{ 
     @autoreleasepool { 
 
        ACSFactSetConfig*  factSetConfigCocoa = [[ ACSFactSetConfig  alloc] initWithTitle: [ACSTextConfigConvertor convertCpp:factSetConfigCpp.title] 
        value: [ACSTextConfigConvertor convertCpp:factSetConfigCpp.value]
        spacing: [NSNumber numberWithUnsignedInt:factSetConfigCpp.spacing]];
        return  factSetConfigCocoa;
   }
}

+(AdaptiveCards::FactSetConfig) convertObj:(ACSFactSetConfig *)factSetConfigObjc {
  AdaptiveCards::FactSetConfig factSetConfigCpp;
  factSetConfigCpp.title = [ACSTextConfigConvertor convertObj:factSetConfigObjc.title];
  factSetConfigCpp.value = [ACSTextConfigConvertor convertObj:factSetConfigObjc.value];
  factSetConfigCpp.spacing = [factSetConfigObjc.spacing unsignedIntValue];
  return  factSetConfigCpp;
}

@end 
