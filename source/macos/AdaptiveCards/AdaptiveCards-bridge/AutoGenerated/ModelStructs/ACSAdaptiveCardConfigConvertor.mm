// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"

#import "ACSAdaptiveCardConfigConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSAdaptiveCardConfigConvertor 

+(ACSAdaptiveCardConfig *) convertCpp:(const AdaptiveCards::AdaptiveCardConfig& )adaptiveCardConfigCpp
{ 
     @autoreleasepool { 
 
        ACSAdaptiveCardConfig*  adaptiveCardConfigCocoa = [[ ACSAdaptiveCardConfig  alloc] initWithAllowCustomStyle: adaptiveCardConfigCpp.allowCustomStyle ];
        return  adaptiveCardConfigCocoa;
   }
}

+(AdaptiveCards::AdaptiveCardConfig) convertObj:(ACSAdaptiveCardConfig *)adaptiveCardConfigObjc {
  AdaptiveCards::AdaptiveCardConfig adaptiveCardConfigCpp;
  adaptiveCardConfigCpp.allowCustomStyle = adaptiveCardConfigObjc.allowCustomStyle;
  return  adaptiveCardConfigCpp;
}

@end 
