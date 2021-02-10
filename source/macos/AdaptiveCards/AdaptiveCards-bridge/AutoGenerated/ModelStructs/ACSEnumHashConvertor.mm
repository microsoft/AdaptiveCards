// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "../../../../../shared/cpp/ObjectModel/EnumMagic.h"

#import "ACSEnumHashConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSEnumHashConvertor 

+(ACSEnumHash *) convertCpp:(const AdaptiveCards::EnumHash& )enumHashCpp
{ 
     @autoreleasepool { 
        return  enumHashCocoa;
   }
}

+(AdaptiveCards::EnumHash) convertObj:(ACSEnumHash *)enumHashObjc {
  return  enumHashCpp;
}

@end 
