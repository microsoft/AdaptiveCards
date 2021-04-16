// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"

#import "ACSImageSizesConfigConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSImageSizesConfigConvertor 

+(ACSImageSizesConfig *) convertCpp:(const AdaptiveCards::ImageSizesConfig& )imageSizesConfigCpp
{ 
     @autoreleasepool { 
 
        ACSImageSizesConfig*  imageSizesConfigCocoa = [[ ACSImageSizesConfig  alloc] initWithSmallSize: [NSNumber numberWithUnsignedInt:imageSizesConfigCpp.smallSize] 
        mediumSize: [NSNumber numberWithUnsignedInt:imageSizesConfigCpp.mediumSize]
        largeSize: [NSNumber numberWithUnsignedInt:imageSizesConfigCpp.largeSize]];
        return  imageSizesConfigCocoa;
   }
}

+(AdaptiveCards::ImageSizesConfig) convertObj:(ACSImageSizesConfig *)imageSizesConfigObjc {
  AdaptiveCards::ImageSizesConfig imageSizesConfigCpp;
  imageSizesConfigCpp.smallSize = [imageSizesConfigObjc.smallSize unsignedIntValue];
  imageSizesConfigCpp.mediumSize = [imageSizesConfigObjc.mediumSize unsignedIntValue];
  imageSizesConfigCpp.largeSize = [imageSizesConfigObjc.largeSize unsignedIntValue];
  return  imageSizesConfigCpp;
}

@end 
