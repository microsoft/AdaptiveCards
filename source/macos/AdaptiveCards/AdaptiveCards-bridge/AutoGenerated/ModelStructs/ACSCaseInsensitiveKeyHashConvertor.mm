// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "../../../../../shared/cpp/ObjectModel/FeatureRegistration.h"

#import "ACSCaseInsensitiveKeyHashConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSCaseInsensitiveKeyHashConvertor 

+(ACSCaseInsensitiveKeyHash *) convertCpp:(const AdaptiveCards::CaseInsensitiveKeyHash& )caseInsensitiveKeyHashCpp
{ 
     @autoreleasepool { 
        return  caseInsensitiveKeyHashCocoa;
   }
}

+(AdaptiveCards::CaseInsensitiveKeyHash) convertObj:(ACSCaseInsensitiveKeyHash *)caseInsensitiveKeyHashObjc {
  return  caseInsensitiveKeyHashCpp;
}

@end 
