// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSColumn_IMPORTED
#define ACSColumn_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "Column.h"
using namespace AdaptiveCards;
#endif

#import "ACSAdaptiveCardParseWarning.h"
#import "ACSParseContext.h"
// #import "ACSRemoteResourceInformation.h"
// #import "ACSValue.h"



#import "ACSCollectionTypeElement.h"
  

@class ACSAdaptiveCardParseWarning;
@class ACSParseContext;
@class ACSRemoteResourceInformation;



@interface ACSColumn : ACSCollectionTypeElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithColumn:(const std::shared_ptr<Column>)cppObj;
#endif

- (NSString * _Nullable)getWidth;
- (void)setWidth:(NSString * _Nonnull)value;
- (void)setWidth:(NSString * _Nonnull)value warnings:(NSArray<ACSAdaptiveCardParseWarning *>* _Nonnull)warnings;
- (NSNumber * _Nullable)getPixelWidth;
- (void)setPixelWidth:(NSNumber * _Nonnull)value;
- (NSArray<ACSBaseCardElement *> * _Nonnull)getItems;
- (void)getResourceInformation:(NSArray<ACSRemoteResourceInformation *>* _Nonnull)resourceInfo;



@end
#endif
