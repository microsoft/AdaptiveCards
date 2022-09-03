//
//  ACRParseWarning
//  ACRParseWarning.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRParseWarningPrivate.h"
#else
#import <AdaptiveCards/ACRParseWarningPrivate.h>
#endif

using namespace AdaptiveCards;

@implementation ACRParseWarning {
    std::shared_ptr<AdaptiveCardParseWarning> _parseWarnings;
}

- (instancetype)initWithParseWarning:(std::shared_ptr<AdaptiveCardParseWarning> const &)parseWarning
{
    self = [super init];
    if (self) {
        _statusCode = (ACRWarningStatusCode)parseWarning->GetStatusCode();
        _reason = [NSString stringWithCString:parseWarning->GetReason().c_str() encoding:NSUTF8StringEncoding];
    }
    return self;
}

@end
