// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSSeparator_IMPORTED
#define ACSSeparator_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "Separator.h"
using namespace AdaptiveCards;
#endif

#import "ACSForegroundColor.h"
#import "ACSSeparatorThickness.h"



  


enum ACSForegroundColor: NSUInteger;
enum ACSSeparatorThickness: NSUInteger;


@interface ACSSeparator : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithSeparator:(const std::shared_ptr<Separator>)cppObj;
#endif

- (ACSSeparatorThickness)getThickness;
- (void)setThickness:(enum ACSSeparatorThickness)value;
- (ACSForegroundColor)getColor;
- (void)setColor:(enum ACSForegroundColor)value;


@end
#endif
