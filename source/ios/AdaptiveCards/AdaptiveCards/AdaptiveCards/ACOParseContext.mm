//
//  ACOParseContext.mm
//  ACOParseContext.h
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACOParseContext.h>
#import <AdaptiveCards/ACOParseContextPrivate.h>
#import <AdaptiveCards/ACRRegistration.h>
#import <AdaptiveCards/BaseElement.h>
#import <AdaptiveCards/ParseContext.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

using namespace AdaptiveCards;

@implementation ACOParseContext {
    std::unique_ptr<ParseContext> _parseContext;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        _parseContext = std::make_unique<ParseContext>();
    }

    return self;
}

- (std::shared_ptr<AdaptiveCards::ActionElementParser> const)getActionParser:(NSString *)elementType
{
    return _parseContext->actionParserRegistration->GetParser(std::string([elementType UTF8String]));
}

@end
