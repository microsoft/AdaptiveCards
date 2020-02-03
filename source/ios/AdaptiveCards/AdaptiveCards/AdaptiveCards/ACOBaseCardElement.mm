//
//  ACOBaseCardElement
//  ACOBaseCardElement.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import "ACOBaseCardElement.h"
#import "ACRRegistrationPrivate.h"
#import "BaseCardElement.h"
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;

@implementation ACOBaseCardElement {
    std::shared_ptr<BaseCardElement> _elem;
}

- (instancetype)initWithBaseCardElement:(std::shared_ptr<BaseCardElement> const &)element
{
    self = [super init];
    if (self && element) {
        _elem = element;
        _type = (ACRCardElementType)element->GetElementType();
    }
    return self;
}

- (instancetype)init
{
    self = [self initWithBaseCardElement:nil];
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
    if (_elem) {
        Json::Value blob = _elem->GetAdditionalProperties();
        Json::FastWriter fastWriter;
        NSString *jsonString =
            [[NSString alloc] initWithCString:fastWriter.write(blob).c_str()
                                     encoding:NSUTF8StringEncoding];
        return (jsonString.length > 0) ? [jsonString dataUsingEncoding:NSUTF8StringEncoding] : nil;
    }
    return nil;
}

- (BOOL)meetsRequirements:(ACOFeatureRegistration *)featureReg
{
    if (_elem) {
        const std::shared_ptr<FeatureRegistration> sharedFReg = [featureReg getSharedFeatureRegistration];
        return _elem->MeetsRequirements(*sharedFReg.get());
    }
    return false;
}

@end
