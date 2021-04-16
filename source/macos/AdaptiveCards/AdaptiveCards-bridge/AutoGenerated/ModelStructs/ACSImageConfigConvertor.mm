// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"
#import "Enums.h"

#import "ACSImageConfigConvertor.h"
#import "ACSImageSizeConvertor.h"
#import "ACSImageSize.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSImageConfigConvertor 

+(ACSImageConfig *) convertCpp:(const AdaptiveCards::ImageConfig& )imageConfigCpp
{ 
     @autoreleasepool { 
 
        ACSImageConfig*  imageConfigCocoa = [[ ACSImageConfig  alloc] initWithImageSize: [ACSImageSizeConvertor convertCpp:imageConfigCpp.imageSize] ];
        return  imageConfigCocoa;
   }
}

+(AdaptiveCards::ImageConfig) convertObj:(ACSImageConfig *)imageConfigObjc {
  AdaptiveCards::ImageConfig imageConfigCpp;
  imageConfigCpp.imageSize = [ACSImageSizeConvertor convertObj:imageConfigObjc.imageSize];
  return  imageConfigCpp;
}

@end 
