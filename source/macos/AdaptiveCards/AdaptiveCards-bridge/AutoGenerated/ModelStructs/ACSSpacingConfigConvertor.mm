// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"

#import "ACSSpacingConfigConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSSpacingConfigConvertor 

+(ACSSpacingConfig *) convertCpp:(const AdaptiveCards::SpacingConfig& )spacingConfigCpp
{ 
     @autoreleasepool { 
 
        ACSSpacingConfig*  spacingConfigCocoa = [[ ACSSpacingConfig  alloc] initWithSmallSpacing: [NSNumber numberWithUnsignedInt:spacingConfigCpp.smallSpacing] 
        defaultSpacing: [NSNumber numberWithUnsignedInt:spacingConfigCpp.defaultSpacing]
        mediumSpacing: [NSNumber numberWithUnsignedInt:spacingConfigCpp.mediumSpacing]
        largeSpacing: [NSNumber numberWithUnsignedInt:spacingConfigCpp.largeSpacing]
        extraLargeSpacing: [NSNumber numberWithUnsignedInt:spacingConfigCpp.extraLargeSpacing]
        paddingSpacing: [NSNumber numberWithUnsignedInt:spacingConfigCpp.paddingSpacing]];
        return  spacingConfigCocoa;
   }
}

+(AdaptiveCards::SpacingConfig) convertObj:(ACSSpacingConfig *)spacingConfigObjc {
  AdaptiveCards::SpacingConfig spacingConfigCpp;
  spacingConfigCpp.smallSpacing = [spacingConfigObjc.smallSpacing unsignedIntValue];
  spacingConfigCpp.defaultSpacing = [spacingConfigObjc.defaultSpacing unsignedIntValue];
  spacingConfigCpp.mediumSpacing = [spacingConfigObjc.mediumSpacing unsignedIntValue];
  spacingConfigCpp.largeSpacing = [spacingConfigObjc.largeSpacing unsignedIntValue];
  spacingConfigCpp.extraLargeSpacing = [spacingConfigObjc.extraLargeSpacing unsignedIntValue];
  spacingConfigCpp.paddingSpacing = [spacingConfigObjc.paddingSpacing unsignedIntValue];
  return  spacingConfigCpp;
}

@end 
