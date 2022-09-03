//
//  ACOParseContextPrivate.h
//  ACOParseContextPrivate
//
//  Copyright © 2019 Microsoft. All rights reserved.
//
#ifdef SWIFT_PACKAGE
#import "ACOParseContext.h"
#import "ParseContext.h"
#else
#import <AdaptiveCards/ACOParseContext.h>
#import <AdaptiveCards/ParseContext.h>
#endif

using namespace AdaptiveCards;

@interface ACOParseContext ()

- (std::shared_ptr<AdaptiveCards::ActionElementParser> const)getActionParser:(NSString *)elementType;

@end
