//
//  ACRParseWarningPrivate
//  ACRParseWarningPrivate.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACRParseWarning.h>
#import <AdaptiveCards/AdaptiveCardParseWarning.h>
#import <Foundation/Foundation.h>

@interface ACRParseWarning ()

- (instancetype)initWithParseWarning:(std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning> const &)parseWarning;

@end
