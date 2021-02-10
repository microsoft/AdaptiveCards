// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSMarkDownBlockTypeConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSMarkDownBlockType.h"

@implementation ACSMarkDownBlockTypeConvertor


+(enum ACSMarkDownBlockType) convertCpp:(AdaptiveCards::MarkDownHtmlGenerator::MarkDownBlockType) markDownBlockTypeCpp
{
  switch(markDownBlockTypeCpp)
  {
    case AdaptiveCards::MarkDownHtmlGenerator::MarkDownBlockType::ContainerBlock:
      return ACSMarkDownBlockType::ACSMarkDownBlockTypeContainerBlock;
    case AdaptiveCards::MarkDownHtmlGenerator::MarkDownBlockType::UnorderedList:
      return ACSMarkDownBlockType::ACSMarkDownBlockTypeUnorderedList;
    case AdaptiveCards::MarkDownHtmlGenerator::MarkDownBlockType::OrderedList:
      return ACSMarkDownBlockType::ACSMarkDownBlockTypeOrderedList;
  }
}


+(AdaptiveCards::MarkDownHtmlGenerator::MarkDownBlockType) convertObj:(enum ACSMarkDownBlockType) markDownBlockTypeObjc
{
  switch(markDownBlockTypeObjc)
  {
    case ACSMarkDownBlockType::ACSMarkDownBlockTypeContainerBlock:
      return AdaptiveCards::MarkDownHtmlGenerator::MarkDownBlockType::ContainerBlock;
    case ACSMarkDownBlockType::ACSMarkDownBlockTypeUnorderedList:
      return AdaptiveCards::MarkDownHtmlGenerator::MarkDownBlockType::UnorderedList;
    case ACSMarkDownBlockType::ACSMarkDownBlockTypeOrderedList:
      return AdaptiveCards::MarkDownHtmlGenerator::MarkDownBlockType::OrderedList;
  }
}

@end
