// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "../../../../../shared/cpp/ObjectModel/HostConfig.h"

#import "ACSSeparatorConfigConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSSeparatorConfigConvertor 

+(ACSSeparatorConfig *) convertCpp:(const AdaptiveCards::SeparatorConfig& )separatorConfigCpp
{ 
     @autoreleasepool { 
 
        ACSSeparatorConfig*  separatorConfigCocoa = [[ ACSSeparatorConfig  alloc] initWithLineThickness: [NSNumber numberWithUnsignedInt:separatorConfigCpp.lineThickness] 
        lineColor: [NSString stringWithUTF8String:separatorConfigCpp.lineColor.c_str()]];
        return  separatorConfigCocoa;
   }
}

+(AdaptiveCards::SeparatorConfig) convertObj:(ACSSeparatorConfig *)separatorConfigObjc {
  AdaptiveCards::SeparatorConfig separatorConfigCpp;
  separatorConfigCpp.lineThickness = [separatorConfigObjc.lineThickness unsignedIntValue];
  separatorConfigCpp.lineColor = std::string([separatorConfigObjc.lineColor UTF8String]);
  return  separatorConfigCpp;
}

@end 
