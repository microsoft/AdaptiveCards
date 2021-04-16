// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"

#import "ACSFontTypesDefinitionConvertor.h"
#import "ACSFontTypeDefinitionConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSFontTypesDefinitionConvertor 

+(ACSFontTypesDefinition *) convertCpp:(const AdaptiveCards::FontTypesDefinition& )fontTypesDefinitionCpp
{ 
     @autoreleasepool { 
 
        ACSFontTypesDefinition*  fontTypesDefinitionCocoa = [[ ACSFontTypesDefinition  alloc] initWithDefaultFontType: [ACSFontTypeDefinitionConvertor convertCpp:fontTypesDefinitionCpp.defaultFontType] 
        monospaceFontType: [ACSFontTypeDefinitionConvertor convertCpp:fontTypesDefinitionCpp.monospaceFontType]];
        return  fontTypesDefinitionCocoa;
   }
}

+(AdaptiveCards::FontTypesDefinition) convertObj:(ACSFontTypesDefinition *)fontTypesDefinitionObjc {
  AdaptiveCards::FontTypesDefinition fontTypesDefinitionCpp;
  fontTypesDefinitionCpp.defaultFontType = [ACSFontTypeDefinitionConvertor convertObj:fontTypesDefinitionObjc.defaultFontType];
  fontTypesDefinitionCpp.monospaceFontType = [ACSFontTypeDefinitionConvertor convertObj:fontTypesDefinitionObjc.monospaceFontType];
  return  fontTypesDefinitionCpp;
}

@end 
