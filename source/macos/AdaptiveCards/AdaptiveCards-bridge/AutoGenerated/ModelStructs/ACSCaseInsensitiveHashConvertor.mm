// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "../../../../../shared/cpp/ObjectModel/EnumMagic.h"

#import "ACSCaseInsensitiveHashConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSCaseInsensitiveHashConvertor 

+(ACSCaseInsensitiveHash *) convertCpp:(const AdaptiveCards::CaseInsensitiveHash& )caseInsensitiveHashCpp
{ 
     @autoreleasepool { 
        return  caseInsensitiveHashCocoa;
   }
}

+(AdaptiveCards::CaseInsensitiveHash) convertObj:(ACSCaseInsensitiveHash *)caseInsensitiveHashObjc {
  return  caseInsensitiveHashCpp;
}

@end 
