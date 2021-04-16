// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"

#import "ACSFontTypeDefinitionConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSFontTypeDefinitionConvertor 

+(ACSFontTypeDefinition *) convertCpp:(const AdaptiveCards::FontTypeDefinition& )fontTypeDefinitionCpp
{ 
     @autoreleasepool { 
 
        ACSFontTypeDefinition*  fontTypeDefinitionCocoa = [[ ACSFontTypeDefinition  alloc] initWithFontFamily: [NSString stringWithUTF8String:fontTypeDefinitionCpp.fontFamily.c_str()] 
        fontSizes: [[ACSFontSizesConfig alloc] init]
        fontWeights: [[ACSFontWeightsConfig alloc] init]];
        return  fontTypeDefinitionCocoa;
   }
}

+(AdaptiveCards::FontTypeDefinition) convertObj:(ACSFontTypeDefinition *)fontTypeDefinitionObjc {
  AdaptiveCards::FontTypeDefinition fontTypeDefinitionCpp;
  fontTypeDefinitionCpp.fontFamily = std::string([fontTypeDefinitionObjc.fontFamily UTF8String]);
//  fontTypeDefinitionCpp.fontSizes = // NEED TO INSERT CODE //;
//  fontTypeDefinitionCpp.fontWeights = // NEED TO INSERT CODE //;
  return  fontTypeDefinitionCpp;
}

@end 
