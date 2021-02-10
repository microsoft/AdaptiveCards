// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "../../../../../shared/cpp/ObjectModel/BaseElement.h"

#import "ACSInternalIdKeyHashConvertor.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSInternalIdKeyHashConvertor 

+(ACSInternalIdKeyHash *) convertCpp:(const AdaptiveCards::InternalIdKeyHash& )internalIdKeyHashCpp
{ 
     @autoreleasepool { 
        return  internalIdKeyHashCocoa;
   }
}

+(AdaptiveCards::InternalIdKeyHash) convertObj:(ACSInternalIdKeyHash *)internalIdKeyHashObjc {
  return  internalIdKeyHashCpp;
}

@end 
