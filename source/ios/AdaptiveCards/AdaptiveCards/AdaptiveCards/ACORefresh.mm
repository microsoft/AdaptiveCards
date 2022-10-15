//
//  ACORefresh
//  ACORefresh.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//
//
//
#import "ACOBaseActionElementPrivate.h"
#import "ACORefreshPrivate.h"

@implementation ACORefresh {
    std::shared_ptr<Refresh> _refreshElement;
}

- (instancetype)init:(std::shared_ptr<Refresh> const &)refreshElement;
{
    self = [super init];
    if (self && refreshElement) {
        _refreshElement = refreshElement;
        NSMutableArray *userIds = [NSMutableArray array];
        for (std::string &userId : refreshElement->GetUserIds()) {
            [userIds addObject:[NSString stringWithCString:userId.c_str() encoding:NSUTF8StringEncoding]];
        }

        self.userIds = [NSArray arrayWithArray:userIds];
        self.action = [[ACOBaseActionElement alloc] initWithBaseActionElement:refreshElement->GetAction()];
    }
    return self;
}

- (instancetype)init:(ACOBaseActionElement *)action userIds:(NSArray<NSString *> *)userIds
{
    std::vector<std::string> userIdsVector;
    if (userIds) {
        for (NSString *userId in userIds) {
            userIdsVector.push_back([userId UTF8String]);
        }
    }
    std::shared_ptr<BaseActionElement> baseAction = nullptr;
    if (action) {
        baseAction = action.element;
    }

    return [self init:std::make_shared<Refresh>(baseAction, userIdsVector)];
}

- (instancetype)init
{
    return [self init:nil];
}

@end
