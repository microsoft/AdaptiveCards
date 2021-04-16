// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"

#import "ACSHighlightColorConfigConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSHighlightColorConfigConvertor 

+(ACSHighlightColorConfig *) convertCpp:(const AdaptiveCards::HighlightColorConfig& )highlightColorConfigCpp
{ 
     @autoreleasepool { 
 
        ACSHighlightColorConfig*  highlightColorConfigCocoa = [[ ACSHighlightColorConfig  alloc] initWithDefaultColor: [NSString stringWithUTF8String:highlightColorConfigCpp.defaultColor.c_str()] 
        subtleColor: [NSString stringWithUTF8String:highlightColorConfigCpp.subtleColor.c_str()]];
        return  highlightColorConfigCocoa;
   }
}

+(AdaptiveCards::HighlightColorConfig) convertObj:(ACSHighlightColorConfig *)highlightColorConfigObjc {
  AdaptiveCards::HighlightColorConfig highlightColorConfigCpp;
  highlightColorConfigCpp.defaultColor = std::string([highlightColorConfigObjc.defaultColor UTF8String]);
  highlightColorConfigCpp.subtleColor = std::string([highlightColorConfigObjc.subtleColor UTF8String]);
  return  highlightColorConfigCpp;
}

@end 
