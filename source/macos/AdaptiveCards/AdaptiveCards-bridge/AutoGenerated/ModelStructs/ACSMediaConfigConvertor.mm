// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "../../../../../shared/cpp/ObjectModel/HostConfig.h"

#import "ACSMediaConfigConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSMediaConfigConvertor 

+(ACSMediaConfig *) convertCpp:(const AdaptiveCards::MediaConfig& )mediaConfigCpp
{ 
     @autoreleasepool { 
 
        ACSMediaConfig*  mediaConfigCocoa = [[ ACSMediaConfig  alloc] initWithDefaultPoster: [NSString stringWithUTF8String:mediaConfigCpp.defaultPoster.c_str()] 
        playButton: [NSString stringWithUTF8String:mediaConfigCpp.playButton.c_str()]
        allowInlinePlayback: mediaConfigCpp.allowInlinePlayback];
        return  mediaConfigCocoa;
   }
}

+(AdaptiveCards::MediaConfig) convertObj:(ACSMediaConfig *)mediaConfigObjc {
  AdaptiveCards::MediaConfig mediaConfigCpp;
  mediaConfigCpp.defaultPoster = std::string([mediaConfigObjc.defaultPoster UTF8String]);
  mediaConfigCpp.playButton = std::string([mediaConfigObjc.playButton UTF8String]);
  mediaConfigCpp.allowInlinePlayback = mediaConfigObjc.allowInlinePlayback;
  return  mediaConfigCpp;
}

@end 
