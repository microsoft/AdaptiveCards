// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSEmphasisStateConvertor.h"
#import "MarkDownBlockParser.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSEmphasisState.h"

@implementation ACSEmphasisStateConvertor


+(enum ACSEmphasisState) convertCpp:(AdaptiveCards::EmphasisParser::EmphasisState) emphasisStateCpp
{
  switch(emphasisStateCpp)
  {
    case AdaptiveCards::EmphasisParser::EmphasisState::Text:
      return ACSEmphasisState::ACSEmphasisStateText;
    case AdaptiveCards::EmphasisParser::EmphasisState::Emphasis:
      return ACSEmphasisState::ACSEmphasisStateEmphasis;
    case AdaptiveCards::EmphasisParser::EmphasisState::Captured:
      return ACSEmphasisState::ACSEmphasisStateCaptured;
  }
}


+(AdaptiveCards::EmphasisParser::EmphasisState) convertObj:(enum ACSEmphasisState) emphasisStateObjc
{
  switch(emphasisStateObjc)
  {
    case ACSEmphasisState::ACSEmphasisStateText:
      return AdaptiveCards::EmphasisParser::EmphasisState::Text;
    case ACSEmphasisState::ACSEmphasisStateEmphasis:
      return AdaptiveCards::EmphasisParser::EmphasisState::Emphasis;
    case ACSEmphasisState::ACSEmphasisStateCaptured:
      return AdaptiveCards::EmphasisParser::EmphasisState::Captured;
  }
}

@end
