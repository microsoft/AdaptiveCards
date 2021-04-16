// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"
#import "Enums.h"

#import "ACSTextConfigConvertor.h"
#import "ACSFontTypeConvertor.h"
#import "ACSForegroundColorConvertor.h"
#import "ACSTextSizeConvertor.h"
#import "ACSTextWeightConvertor.h"
#import "ACSFontType.h"
#import "ACSForegroundColor.h"
#import "ACSTextSize.h"
#import "ACSTextWeight.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSTextConfigConvertor 

+(ACSTextConfig *) convertCpp:(const AdaptiveCards::TextConfig& )textConfigCpp
{ 
     @autoreleasepool { 
 
        ACSTextConfig*  textConfigCocoa = [[ ACSTextConfig  alloc] initWithWeight: [ACSTextWeightConvertor convertCpp:textConfigCpp.weight] 
        size: [ACSTextSizeConvertor convertCpp:textConfigCpp.size]
        fontType: [ACSFontTypeConvertor convertCpp:textConfigCpp.fontType]
        color: [ACSForegroundColorConvertor convertCpp:textConfigCpp.color]
        isSubtle: textConfigCpp.isSubtle
        wrap: textConfigCpp.wrap
        maxWidth: [NSNumber numberWithUnsignedInt:textConfigCpp.maxWidth]];
        return  textConfigCocoa;
   }
}

+(AdaptiveCards::TextConfig) convertObj:(ACSTextConfig *)textConfigObjc {
  AdaptiveCards::TextConfig textConfigCpp;
  textConfigCpp.weight = [ACSTextWeightConvertor convertObj:textConfigObjc.weight];
  textConfigCpp.size = [ACSTextSizeConvertor convertObj:textConfigObjc.size];
  textConfigCpp.fontType = [ACSFontTypeConvertor convertObj:textConfigObjc.fontType];
  textConfigCpp.color = [ACSForegroundColorConvertor convertObj:textConfigObjc.color];
  textConfigCpp.isSubtle = textConfigObjc.isSubtle;
  textConfigCpp.wrap = textConfigObjc.wrap;
  textConfigCpp.maxWidth = [textConfigObjc.maxWidth unsignedIntValue];
  return  textConfigCpp;
}

@end 
