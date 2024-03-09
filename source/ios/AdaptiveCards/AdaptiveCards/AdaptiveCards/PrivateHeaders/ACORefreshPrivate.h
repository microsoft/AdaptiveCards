//
//  ACORefresh.h
//  ACORefresh
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACORefresh.h"
#import "Refresh.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACORefresh.h>
#import <AdaptiveCards/Refresh.h>
#endif

using namespace AdaptiveCards;

@interface ACORefresh ()

- (instancetype)init:(std::shared_ptr<Refresh> const &)refreshElement;

@end
