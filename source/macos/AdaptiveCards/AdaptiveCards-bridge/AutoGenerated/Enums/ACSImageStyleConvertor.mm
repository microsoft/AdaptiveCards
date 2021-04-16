// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSImageStyleConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSImageStyle.h"

@implementation ACSImageStyleConvertor


+(enum ACSImageStyle) convertCpp:(AdaptiveCards::ImageStyle) imageStyleCpp
{
  switch(imageStyleCpp)
  {
    case AdaptiveCards::ImageStyle::Default:
      return ACSImageStyle::ACSImageStyleDefault;
    case AdaptiveCards::ImageStyle::Person:
      return ACSImageStyle::ACSImageStylePerson;
  }
}


+(AdaptiveCards::ImageStyle) convertObj:(enum ACSImageStyle) imageStyleObjc
{
  switch(imageStyleObjc)
  {
    case ACSImageStyle::ACSImageStyleDefault:
      return AdaptiveCards::ImageStyle::Default;
    case ACSImageStyle::ACSImageStylePerson:
      return AdaptiveCards::ImageStyle::Person;
  }
}

@end
