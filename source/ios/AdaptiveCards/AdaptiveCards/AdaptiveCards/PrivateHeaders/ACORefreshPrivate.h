//
//  ACORefresh.h
//  ACORefresh
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACORefresh.h"
#import "Refresh.h"
#else
#import <AdaptiveCards/ACORefresh.h>
#import <AdaptiveCards/Refresh.h>
#endif

using namespace AdaptiveCards;

@interface ACORefresh ()

- (instancetype)init:(std::shared_ptr<Refresh> const &)refreshElement;

@end
