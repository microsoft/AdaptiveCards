// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSInlineElementTypeConvertor.h"
#import "Enums.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSInlineElementType.h"

@implementation ACSInlineElementTypeConvertor


+(enum ACSInlineElementType) convertCpp:(AdaptiveCards::InlineElementType) inlineElementTypeCpp
{
  switch(inlineElementTypeCpp)
  {
    case AdaptiveCards::InlineElementType::TextRun:
      return ACSInlineElementType::ACSInlineElementTypeTextRun;
  }
}


+(AdaptiveCards::InlineElementType) convertObj:(enum ACSInlineElementType) inlineElementTypeObjc
{
  switch(inlineElementTypeObjc)
  {
    case ACSInlineElementType::ACSInlineElementTypeTextRun:
      return AdaptiveCards::InlineElementType::TextRun;
  }
}

@end
