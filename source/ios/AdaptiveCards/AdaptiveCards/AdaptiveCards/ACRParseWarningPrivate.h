//
//  ACRParseWarningPrivate
//  ACRParseWarningPrivate.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "AdaptiveCardParseWarning.h"
#import <Foundation/Foundation.h>
#import "ACRParseWarning.h"

@interface ACRParseWarning()

- (instancetype)initWithParseWarning:(std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning> const &)parseWarning;

@end
