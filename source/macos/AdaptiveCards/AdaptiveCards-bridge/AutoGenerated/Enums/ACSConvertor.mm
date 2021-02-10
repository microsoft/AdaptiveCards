// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACS.h"

@implementation ACSConvertor


+(enum ACS) convertCpp:(AdaptiveCards::MarkDownEmphasisHtmlGenerator::) Cpp
{
  switch(Cpp)
  {
    case AdaptiveCards::MarkDownEmphasisHtmlGenerator::::Left:
      return ACS::ACSLeft;
    case AdaptiveCards::MarkDownEmphasisHtmlGenerator::::Right:
      return ACS::ACSRight;
  }
}


+(AdaptiveCards::MarkDownEmphasisHtmlGenerator::) convertObj:(enum ACS) Objc
{
  switch(Objc)
  {
    case ACS::ACSLeft:
      return AdaptiveCards::MarkDownEmphasisHtmlGenerator::::Left;
    case ACS::ACSRight:
      return AdaptiveCards::MarkDownEmphasisHtmlGenerator::::Right;
  }
}

@end
