//
//  ACORefresh
//  ACORefresh.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#ifdef USE_AC_SWIFT_PACKAGE
#import "ACOBaseActionElement.h"
#else
#import <AdaptiveCards/ACOBaseActionElement.h>
#endif
#import <Foundation/Foundation.h>

@interface ACORefresh : NSObject

@property ACOBaseActionElement *action;
@property NSArray<NSString *> *userIds;

- (instancetype)init:(ACOBaseActionElement *)action userIds:(NSArray<NSString *> *)userIds;

@end
