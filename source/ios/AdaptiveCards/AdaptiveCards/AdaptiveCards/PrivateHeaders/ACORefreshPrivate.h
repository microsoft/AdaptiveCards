//
//  ACORefresh.h
//  ACORefresh
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACORefresh.h>
#import <AdaptiveCards/Refresh.h>

using namespace AdaptiveCards;

@interface ACORefresh ()

- (instancetype)init:(std::shared_ptr<Refresh> const &)refreshElement;

@end
