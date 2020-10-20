//
//  ACOBaseActionElement
//  ACOBaseActionElement.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOBaseActionElement.h"
#import "ACRRegistrationPrivate.h"
#import "BaseActionElement.h"
#import "OpenUrlAction.h"
#import "SubmitAction.h"
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;

@implementation ACOBaseActionElement {
    std::shared_ptr<BaseActionElement> _elem;
}

- (instancetype)init
{
    return [self initWithBaseActionElement:nil];
}

- (instancetype)initWithBaseActionElement:(std::shared_ptr<BaseActionElement> const &)element
{
    self = [super init];
    if (self) {
        [self setElem:element];
    }
    return self;
}

- (std::shared_ptr<BaseActionElement>)element
{
    return _elem;
}

- (void)setElem:(std::shared_ptr<BaseActionElement> const &)element
{
    if (element) {
        _type = (ACRActionType)element->GetElementType();
        _sentiment = [NSString stringWithCString:element->GetStyle().c_str() encoding:NSUTF8StringEncoding];
    }
    _elem = element;
}

- (NSData *)additionalProperty
{
    if (_elem) {
        Json::Value blob = _elem->GetAdditionalProperties();
        Json::StreamWriterBuilder streamWriterBuilder;
        auto writer = streamWriterBuilder.newStreamWriter();
        std::stringstream sstream;
        writer->write(blob, &sstream);
        NSString *jsonString =
            [[NSString alloc] initWithCString:sstream.str().c_str()
                                     encoding:NSUTF8StringEncoding];
        return (jsonString.length > 0) ? [jsonString dataUsingEncoding:NSUTF8StringEncoding] : nil;
    }
    return nil;
}

- (NSString *)title
{
    if (_elem) {
        return [NSString stringWithCString:_elem->GetTitle().c_str() encoding:NSUTF8StringEncoding];
    }
    return @"";
}

- (NSString *)elementId
{
    if (_elem) {
        return [NSString stringWithCString:_elem->GetId().c_str() encoding:NSUTF8StringEncoding];
    }
    return @"";
}

- (NSString *)url
{
    if (_elem && _type == ACROpenUrl) {
        std::shared_ptr<OpenUrlAction> openUrlAction = std::dynamic_pointer_cast<OpenUrlAction>(_elem);
        return [NSString stringWithCString:openUrlAction->GetUrl().c_str() encoding:NSUTF8StringEncoding];
    }
    return @"";
}

- (NSString *)data
{
    if (_elem && _type == ACRSubmit) {
        std::shared_ptr<SubmitAction> submitAction = std::dynamic_pointer_cast<SubmitAction>(_elem);
        return [NSString stringWithCString:submitAction->GetDataJson().c_str() encoding:NSUTF8StringEncoding];
    }
    return @"";
}

- (BOOL)meetsRequirements:(ACOFeatureRegistration *)featureReg
{
    if (_elem) {
        const std::shared_ptr<FeatureRegistration> sharedFReg = [featureReg getSharedFeatureRegistration];
        return _elem->MeetsRequirements(*sharedFReg.get());
    }
    return false;
}

+ (NSNumber *)getKey:(ACRActionType)actionType
{
    NSNumber *key = nil;
    switch (actionType) {
        case ACRShowCard:
            key = [NSNumber numberWithInt:static_cast<int>(ActionType::ShowCard)];
        case ACRSubmit:
            key = [NSNumber numberWithInt:static_cast<int>(ActionType::Submit)];
        case ACROpenUrl:
            key = [NSNumber numberWithInt:static_cast<int>(ActionType::OpenUrl)];
        case ACRToggleVisibility:
            key = [NSNumber numberWithInt:static_cast<int>(ActionType::ToggleVisibility)];
        case ACRUnknownAction:
        default:
            key = [NSNumber numberWithInt:static_cast<int>(ActionType::UnknownAction)];
    }

    return key;
}

@end
