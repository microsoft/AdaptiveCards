//
//  ACOBaseCardElement
//  ACOBaseCardElement.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACOBaseCardElement.h"
#import "BaseCardElement.h"

using namespace AdaptiveCards;

@implementation ACOBaseCardElement
{
    std::shared_ptr<BaseCardElement> _elem;
}

- (instancetype)init
{
    self = [super init];
    return self;
}

- (std::shared_ptr<BaseCardElement>)element
{
    return _elem;
}

- (void)setElem:(std::shared_ptr<BaseCardElement> const &)elem
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
