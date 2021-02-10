// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSSemanticVersion_IMPORTED
#define ACSSemanticVersion_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "SemanticVersion.h"
using namespace AdaptiveCards;
#endif




  




@interface ACSSemanticVersion : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithSemanticVersion:(const std::shared_ptr<SemanticVersion>)cppObj;
#endif

- (NSNumber * _Nullable)getMajor;
- (NSNumber * _Nullable)getMinor;
- (NSNumber * _Nullable)getBuild;
- (NSNumber * _Nullable)getRevision;


@end
#endif
