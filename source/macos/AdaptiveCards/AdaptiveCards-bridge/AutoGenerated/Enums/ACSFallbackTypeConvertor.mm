// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSFallbackTypeConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSFallbackType.h"

@implementation ACSFallbackTypeConvertor


+(enum ACSFallbackType) convertCpp:(AdaptiveCards::FallbackType) fallbackTypeCpp
{
  switch(fallbackTypeCpp)
  {
    case AdaptiveCards::FallbackType::None:
      return ACSFallbackType::ACSFallbackTypeNone;
    case AdaptiveCards::FallbackType::Drop:
      return ACSFallbackType::ACSFallbackTypeDrop;
    case AdaptiveCards::FallbackType::Content:
      return ACSFallbackType::ACSFallbackTypeContent;
  }
}


+(AdaptiveCards::FallbackType) convertObj:(enum ACSFallbackType) fallbackTypeObjc
{
  switch(fallbackTypeObjc)
  {
    case ACSFallbackType::ACSFallbackTypeNone:
      return AdaptiveCards::FallbackType::None;
    case ACSFallbackType::ACSFallbackTypeDrop:
      return AdaptiveCards::FallbackType::Drop;
    case ACSFallbackType::ACSFallbackTypeContent:
      return AdaptiveCards::FallbackType::Content;
  }
}

@end
