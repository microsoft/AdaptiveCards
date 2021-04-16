// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "RemoteResourceInformation.h"

#import "ACSRemoteResourceInformationConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSRemoteResourceInformationConvertor 

+(ACSRemoteResourceInformation *) convertCpp:(const AdaptiveCards::RemoteResourceInformation& )remoteResourceInformationCpp
{ 
     @autoreleasepool { 
 
        ACSRemoteResourceInformation*  remoteResourceInformationCocoa = [[ ACSRemoteResourceInformation  alloc] initWithUrl: [NSString stringWithUTF8String:remoteResourceInformationCpp.url.c_str()] 
        mimeType: [NSString stringWithUTF8String:remoteResourceInformationCpp.mimeType.c_str()]];
        return  remoteResourceInformationCocoa;
   }
}

+(AdaptiveCards::RemoteResourceInformation) convertObj:(ACSRemoteResourceInformation *)remoteResourceInformationObjc {
  AdaptiveCards::RemoteResourceInformation remoteResourceInformationCpp;
  remoteResourceInformationCpp.url = std::string([remoteResourceInformationObjc.url UTF8String]);
  remoteResourceInformationCpp.mimeType = std::string([remoteResourceInformationObjc.mimeType UTF8String]);
  return  remoteResourceInformationCpp;
}

@end 
