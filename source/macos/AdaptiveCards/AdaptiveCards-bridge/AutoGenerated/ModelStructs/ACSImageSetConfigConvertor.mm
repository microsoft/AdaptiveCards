// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"
#import "Enums.h"

#import "ACSImageSetConfigConvertor.h"
#import "ACSImageSizeConvertor.h"
#import "ACSImageSize.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSImageSetConfigConvertor 

+(ACSImageSetConfig *) convertCpp:(const AdaptiveCards::ImageSetConfig& )imageSetConfigCpp
{ 
     @autoreleasepool { 
 
        ACSImageSetConfig*  imageSetConfigCocoa = [[ ACSImageSetConfig  alloc] initWithImageSize: [ACSImageSizeConvertor convertCpp:imageSetConfigCpp.imageSize] 
        maxImageHeight: [NSNumber numberWithUnsignedInt:imageSetConfigCpp.maxImageHeight]];
        return  imageSetConfigCocoa;
   }
}

+(AdaptiveCards::ImageSetConfig) convertObj:(ACSImageSetConfig *)imageSetConfigObjc {
  AdaptiveCards::ImageSetConfig imageSetConfigCpp;
  imageSetConfigCpp.imageSize = [ACSImageSizeConvertor convertObj:imageSetConfigObjc.imageSize];
  imageSetConfigCpp.maxImageHeight = [imageSetConfigObjc.maxImageHeight unsignedIntValue];
  return  imageSetConfigCpp;
}

@end 
