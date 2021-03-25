//
//  ACORefresh
//  ACORefresh.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOBaseActionElement.h"

@interface ACORefresh : NSObject

@property ACOBaseActionElement *action;
@property NSArray<NSString *> *userIds;

- (instancetype)init:(ACOBaseActionElement *)action userIds:(NSArray<NSString *> *)userIds;

@end
