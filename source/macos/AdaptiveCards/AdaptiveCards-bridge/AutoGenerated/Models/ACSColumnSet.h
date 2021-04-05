// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSColumnSet_IMPORTED
#define ACSColumnSet_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "ColumnSet.h"
using namespace AdaptiveCards;
#endif

#import "ACSColumn.h"
#import "ACSParseContext.h"
#import "ACSHorizontalAlignment.h"
// #import "ACSRemoteResourceInformation.h"
// #import "ACSValue.h"



#import "ACSCollectionTypeElement.h"
  

@class ACSColumn;
@class ACSParseContext;
@class ACSRemoteResourceInformation;

enum ACSHorizontalAlignment: NSUInteger;

@interface ACSColumnSet : ACSCollectionTypeElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithColumnSet:(const std::shared_ptr<ColumnSet>)cppObj;
#endif

- (NSArray<ACSColumn *> * _Nonnull)getColumns;
- (void)getResourceInformation:(NSArray<ACSRemoteResourceInformation *>* _Nonnull)resourceInfo;

- (ACSHorizontalAlignment)getHorizontalAlignment;
- (void)setHorizontalAlignment:(enum ACSHorizontalAlignment)value;



@end
#endif
