//
//  ACOBaseActionElement
//  ACOBaseActionElement.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOBaseActionElement.h"
#import "ACRRegistrationPrivate.h"
#import "BaseActionElement.h"
#import "ExecuteAction.h"
#import "OpenUrlAction.h"
#import "SubmitAction.h"
#import "UnknownAction.h"
#import "UtiliOS.h"
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

+ (instancetype)getACOActionElementFromAdaptiveElement:(std::shared_ptr<BaseActionElement> const &)element
{
    ACOBaseActionElement *actionElement = nil;

    if (!element) {
        return nil;
    }

    AdaptiveCards::ActionType type = element->GetElementType();
    if (element->GetElementType() == AdaptiveCards::ActionType::UnknownAction) {
        std::shared_ptr<UnknownAction> unknownAction = std::dynamic_pointer_cast<UnknownAction>(element);
        // we get back a deserialized action object by calling a custom parser registered via host
        actionElement = deserializeUnknownActionToCustomAction(unknownAction);
    } else {
        actionElement = [[ACOBaseActionElement alloc] initWithBaseActionElement:element];
    }

    if (type == ActionType::OpenUrl) {
        actionElement.accessibilityTraits |= UIAccessibilityTraitLink;
    } else if (type == ActionType::UnknownAction) {
        actionElement.accessibilityTraits |= actionElement.accessibilityTraits;
    } else {
        actionElement.accessibilityTraits |= UIAccessibilityTraitButton;
    }
    return actionElement;
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
        if (blob.empty()) {
            return nil;
        }
        return JsonToNSData(blob);
    }
    return nil;
}

- (NSString *)title
{
    if (_elem) {
        return [NSString stringWithCString:_elem->GetTitle().c_str() encoding:NSUTF8StringEncoding];
    }
    return nil;
}

- (NSString *)elementId
{
    if (_elem) {
        return [NSString stringWithCString:_elem->GetId().c_str() encoding:NSUTF8StringEncoding];
    }
    return nil;
}

- (NSString *)url
{
    if (_elem && _type == ACROpenUrl) {
        std::shared_ptr<OpenUrlAction> openUrlAction = std::dynamic_pointer_cast<OpenUrlAction>(_elem);
        return [NSString stringWithCString:openUrlAction->GetUrl().c_str() encoding:NSUTF8StringEncoding];
    }
    return nil;
}

- (NSString *)data
{
    if (_elem) {
        std::string data;
        if (_type == ACRSubmit) {
            std::shared_ptr<SubmitAction> submitAction = std::dynamic_pointer_cast<SubmitAction>(_elem);
            data = submitAction->GetDataJson();
        }

        if (_type == ACRExecute) {
            std::shared_ptr<ExecuteAction> executeAction = std::dynamic_pointer_cast<ExecuteAction>(_elem);
            data = executeAction->GetDataJson();
        }

        if (!data.empty()) {
            return [NSString stringWithCString:data.c_str() encoding:NSUTF8StringEncoding];
        }
    }
    return nil;
}

- (NSString *)verb
{
    if (_elem && _type == ACRExecute) {
        std::shared_ptr<ExecuteAction> executeAction = std::dynamic_pointer_cast<ExecuteAction>(_elem);
        return [NSString stringWithCString:executeAction->GetVerb().c_str() encoding:NSUTF8StringEncoding];
    }
    return nil;
}

- (BOOL)isEnabled
{
    if (_elem) {
        return _elem->GetIsEnabled();
    }
    return YES;
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
            break;
        case ACRSubmit:
            key = [NSNumber numberWithInt:static_cast<int>(ActionType::Submit)];
            break;
        case ACROpenUrl:
            key = [NSNumber numberWithInt:static_cast<int>(ActionType::OpenUrl)];
            break;
        case ACRToggleVisibility:
            key = [NSNumber numberWithInt:static_cast<int>(ActionType::ToggleVisibility)];
            break;
        case ACRExecute:
            key = [NSNumber numberWithInt:static_cast<int>(ActionType::Execute)];
            break;
        case ACROverflow:
            key = [NSNumber numberWithInt:static_cast<int>(ActionType::Overflow)];
            break;
        case ACRUnknownAction:
        default:
            key = [NSNumber numberWithInt:static_cast<int>(ActionType::UnknownAction)];
    }

    return key;
}

@end
