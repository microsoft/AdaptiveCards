//
//  ACRParseWarningPrivate
//  ACRParseWarningPrivate.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACRParseWarning.h"
#import "AdaptiveCardParseWarning.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACRParseWarning.h>
#import <AdaptiveCards/AdaptiveCardParseWarning.h>
#endif
#import <Foundation/Foundation.h>

@interface ACRParseWarning ()

- (instancetype)initWithParseWarning:(std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning> const &)parseWarning;

@end
