// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"

#import "ACSColorsConfigConvertor.h"
#import "ACSColorConfigConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSColorsConfigConvertor 

+(ACSColorsConfig *) convertCpp:(const AdaptiveCards::ColorsConfig& )colorsConfigCpp
{ 
     @autoreleasepool { 
 
        ACSColorsConfig*  colorsConfigCocoa = [[ ACSColorsConfig  alloc] initWithDefaultColor: [ACSColorConfigConvertor convertCpp:colorsConfigCpp.defaultColor] 
        accent: [ACSColorConfigConvertor convertCpp:colorsConfigCpp.accent]
        dark: [ACSColorConfigConvertor convertCpp:colorsConfigCpp.dark]
        light: [ACSColorConfigConvertor convertCpp:colorsConfigCpp.light]
        good: [ACSColorConfigConvertor convertCpp:colorsConfigCpp.good]
        warning: [ACSColorConfigConvertor convertCpp:colorsConfigCpp.warning]
        attention: [ACSColorConfigConvertor convertCpp:colorsConfigCpp.attention]];
        return  colorsConfigCocoa;
   }
}

+(AdaptiveCards::ColorsConfig) convertObj:(ACSColorsConfig *)colorsConfigObjc {
  AdaptiveCards::ColorsConfig colorsConfigCpp;
  colorsConfigCpp.defaultColor = [ACSColorConfigConvertor convertObj:colorsConfigObjc.defaultColor];
  colorsConfigCpp.accent = [ACSColorConfigConvertor convertObj:colorsConfigObjc.accent];
  colorsConfigCpp.dark = [ACSColorConfigConvertor convertObj:colorsConfigObjc.dark];
  colorsConfigCpp.light = [ACSColorConfigConvertor convertObj:colorsConfigObjc.light];
  colorsConfigCpp.good = [ACSColorConfigConvertor convertObj:colorsConfigObjc.good];
  colorsConfigCpp.warning = [ACSColorConfigConvertor convertObj:colorsConfigObjc.warning];
  colorsConfigCpp.attention = [ACSColorConfigConvertor convertObj:colorsConfigObjc.attention];
  return  colorsConfigCpp;
}

@end 
