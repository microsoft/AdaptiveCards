//
//  ACOBaseActionElement
//  ACOBaseActionElement.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACOBaseActionElement.h"
#import "BaseActionElement.h"

using namespace AdaptiveCards;

@implementation ACOBaseActionElement
{
    std::shared_ptr<BaseActionElement> _elem;
}

- (instancetype)init
{
    self = [super init];
    return self;
}

- (std::shared_ptr<BaseActionElement>)getElem
{
    return _elem;
}

- (void)setElem:(std::shared_ptr<BaseActionElement> const &)elem
{
    _elem = elem;
}

- (NSData *)additionalProperty
{
    if(_elem){
        Json::Value blob = _elem->GetAdditionalProperties();
        Json::FastWriter fastWriter;
        NSString *jsonString =
            [[NSString alloc] initWithCString:fastWriter.write(blob).c_str() encoding:NSUTF8StringEncoding];
        return (jsonString.length > 0)? [jsonString dataUsingEncoding:NSUTF8StringEncoding] : nil;
    }
    return nil;
}

@end
