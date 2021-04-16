// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"

#import "ACSColorConfigConvertor.h"
#import "ACSHighlightColorConfigConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSColorConfigConvertor 

+(ACSColorConfig *) convertCpp:(const AdaptiveCards::ColorConfig& )colorConfigCpp
{ 
     @autoreleasepool { 
 
        ACSColorConfig*  colorConfigCocoa = [[ ACSColorConfig  alloc] initWithDefaultColor: [NSString stringWithUTF8String:colorConfigCpp.defaultColor.c_str()] 
        subtleColor: [NSString stringWithUTF8String:colorConfigCpp.subtleColor.c_str()]
        highlightColors: [ACSHighlightColorConfigConvertor convertCpp:colorConfigCpp.highlightColors]];
        return  colorConfigCocoa;
   }
}

+(AdaptiveCards::ColorConfig) convertObj:(ACSColorConfig *)colorConfigObjc {
  AdaptiveCards::ColorConfig colorConfigCpp;
  colorConfigCpp.defaultColor = std::string([colorConfigObjc.defaultColor UTF8String]);
  colorConfigCpp.subtleColor = std::string([colorConfigObjc.subtleColor UTF8String]);
  colorConfigCpp.highlightColors = [ACSHighlightColorConfigConvertor convertObj:colorConfigObjc.highlightColors];
  return  colorConfigCpp;
}

@end 
