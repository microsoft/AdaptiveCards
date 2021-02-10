// DO NOT EDIT - Auto generated
// Generated with objc_convertor_enum.j2

#import "ACSTupleIndexConvertor.h"
#import "../../../../../shared/cpp/ObjectModel/ParseContext.h"
// #import "ConversionUtils.h"
#import "SwiftInterfaceHeader.h"
#import "ACSTupleIndex.h"

@implementation ACSTupleIndexConvertor


+(enum ACSTupleIndex) convertCpp:(AdaptiveCards::ParseContext::TupleIndex) tupleIndexCpp
{
  switch(tupleIndexCpp)
  {
    case AdaptiveCards::ParseContext::TupleIndex::Id:
      return ACSTupleIndex::ACSTupleIndexId;
    case AdaptiveCards::ParseContext::TupleIndex::InternalId:
      return ACSTupleIndex::ACSTupleIndexInternalId;
    case AdaptiveCards::ParseContext::TupleIndex::IsFallback:
      return ACSTupleIndex::ACSTupleIndexIsFallback;
  }
}


+(AdaptiveCards::ParseContext::TupleIndex) convertObj:(enum ACSTupleIndex) tupleIndexObjc
{
  switch(tupleIndexObjc)
  {
    case ACSTupleIndex::ACSTupleIndexId:
      return AdaptiveCards::ParseContext::TupleIndex::Id;
    case ACSTupleIndex::ACSTupleIndexInternalId:
      return AdaptiveCards::ParseContext::TupleIndex::InternalId;
    case ACSTupleIndex::ACSTupleIndexIsFallback:
      return AdaptiveCards::ParseContext::TupleIndex::IsFallback;
  }
}

@end
