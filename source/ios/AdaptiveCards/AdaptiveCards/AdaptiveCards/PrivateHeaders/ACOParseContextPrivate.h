//
//  ACOParseContextPrivate.h
//  ACOParseContextPrivate
//
//  Copyright © 2019 Microsoft. All rights reserved.
//
#import "ACOParseContext.h"
#import "ParseContext.h"

using namespace AdaptiveCards;

@interface ACOParseContext ()

- (std::shared_ptr<AdaptiveCards::ActionElementParser> const)getActionParser:(NSString *)elementType;

@end
