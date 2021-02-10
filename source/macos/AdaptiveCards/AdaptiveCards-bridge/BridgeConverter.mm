#import <Foundation/Foundation.h>
#import "SwiftInterfaceHeader.h"
#import "BridgeConverter.h"

using namespace AdaptiveCards;
using namespace std;

NSString *const ACRParseErrorDomain = @"ACRParseErrorDomain";

@implementation BridgeConverter

+ (NSString *) getString:(string) stringCpp
{
    return [NSString stringWithUTF8String:stringCpp.c_str()];
};

+ (string)getStringCpp:(NSString *)string
{
    return std::string([string UTF8String]);
};

+ (ACSParseResult *) parseAdaptiveCardFromJSON:(NSString *)jsonString
{
    auto jsonStringCpp = string([jsonString UTF8String]);
    auto resultCpp = AdaptiveCard::DeserializeFromString(jsonStringCpp, "1.3");
    return [[ACSParseResult alloc] initWithParseResult:resultCpp];
};

+ (ACSHostConfigParseResult *)parseHostConfigFromJSON:(NSString *)jsonString
{
    ACSHostConfigParseResult *result = nil;
    if (jsonString) {
        try {
            std::shared_ptr<HostConfig> cHostConfig = std::make_shared<HostConfig>(AdaptiveCards::HostConfig::DeserializeFromString(string([jsonString UTF8String])));
            ACSHostConfig *config = [[ACSHostConfig alloc] initWithHostConfig:cHostConfig];
            result = [[ACSHostConfigParseResult alloc] initWithConfig:config error:nil];
        } catch (const AdaptiveCardParseException &e) {
            ErrorStatusCode errorStatusCode = e.GetStatusCode();
            NSInteger errorCode = (long)errorStatusCode;
            NSError *parseError = [NSError errorWithDomain:ACRParseErrorDomain
                                                      code:errorCode
                                                  userInfo:nil];
            result = [[ACSHostConfigParseResult alloc] initWithConfig:nil error:parseError];
        }
    }
    return result;
}

+ (ACSBaseElement *)convertFromBaseElement:(std::shared_ptr<BaseElement>)baseElementCpp
{
    if (auto baseCardElement = dynamic_pointer_cast<BaseCardElement>(baseElementCpp))
        return [BridgeConverter convertFromBaseCardElement:baseCardElement];
    if (auto baseActionElement = dynamic_pointer_cast<BaseActionElement>(baseElementCpp))
        return [BridgeConverter convertFromBaseActionElement:baseActionElement];
    
    // Can't downcast any further. Returning as ACSBaseElement.
    return [[ACSBaseElement alloc] initWithBaseElement:baseElementCpp];
};

+ (ACSBaseCardElement *)convertFromBaseCardElement:(std::shared_ptr<BaseCardElement>)baseCardElementCpp
{
    if (auto baseInputElement = dynamic_pointer_cast<BaseInputElement>(baseCardElementCpp))
        return [BridgeConverter convertFromBaseInputElement:baseInputElement];
    if (auto collectionTypeElement = dynamic_pointer_cast<CollectionTypeElement>(baseCardElementCpp))
        return [BridgeConverter covertFromCollectionTypeElement:collectionTypeElement];
    
    if (auto image = dynamic_pointer_cast<Image>(baseCardElementCpp))
        return [[ACSImage alloc] initWithImage:image];
    if (auto media = dynamic_pointer_cast<Media>(baseCardElementCpp))
        return [[ACSMedia alloc] initWithMedia:media];
    if (auto textBlock = dynamic_pointer_cast<TextBlock>(baseCardElementCpp))
        return [[ACSTextBlock alloc] initWithTextBlock:textBlock];
    if (auto richTextBlock = dynamic_pointer_cast<RichTextBlock>(baseCardElementCpp))
        return [[ACSRichTextBlock alloc] initWithRichTextBlock:richTextBlock];
    if (auto imageSet = dynamic_pointer_cast<ImageSet>(baseCardElementCpp))
        return [[ACSImageSet alloc] initWithImageSet:imageSet];
    if (auto factSet = dynamic_pointer_cast<FactSet>(baseCardElementCpp))
        return [[ACSFactSet alloc] initWithFactSet:factSet];
    if (auto actionSet = dynamic_pointer_cast<ActionSet>(baseCardElementCpp))
        return [[ACSActionSet alloc] initWithActionSet:actionSet];
    if (auto unknownElement = dynamic_pointer_cast<UnknownElement>(baseCardElementCpp))
        return [[ACSUnknownElement alloc] initWithUnknownElement:unknownElement];
    
    // Can't downcast any further. Returning as ACSBaseElement.
    return [[ACSBaseCardElement alloc] initWithBaseCardElement:baseCardElementCpp];
}

+ (ACSBaseActionElement *)convertFromBaseActionElement:(std::shared_ptr<BaseActionElement>)baseActionElementCpp
{
    if (auto showCardAction = dynamic_pointer_cast<ShowCardAction>(baseActionElementCpp))
        return [[ACSShowCardAction alloc] initWithShowCardAction:showCardAction];
    if (auto toggleVisibilityAction = dynamic_pointer_cast<ToggleVisibilityAction>(baseActionElementCpp))
        return [[ACSToggleVisibilityAction alloc] initWithToggleVisibilityAction:toggleVisibilityAction];
    if (auto openUrlAction = dynamic_pointer_cast<OpenUrlAction>(baseActionElementCpp))
        return [[ACSOpenUrlAction alloc] initWithOpenUrlAction:openUrlAction];
    if (auto submitAction = dynamic_pointer_cast<SubmitAction>(baseActionElementCpp))
        return [[ACSSubmitAction alloc] initWithSubmitAction:submitAction];
    if (auto unknownAction = dynamic_pointer_cast<UnknownAction>(baseActionElementCpp))
        return [[ACSUnknownAction alloc] initWithUnknownAction:unknownAction];
    
    // Can't downcast any further. Returning as ACSBaseElement.
    return [[ACSBaseActionElement alloc] initWithBaseActionElement:baseActionElementCpp];
}

+ (ACSBaseInputElement *)convertFromBaseInputElement:(std::shared_ptr<BaseInputElement>)baseInputElementCpp
{
    if (auto textInput = dynamic_pointer_cast<TextInput>(baseInputElementCpp))
        return [[ACSTextInput alloc] initWithTextInput:textInput];
    if (auto toggleInput = dynamic_pointer_cast<ToggleInput>(baseInputElementCpp))
        return [[ACSToggleInput alloc] initWithToggleInput:toggleInput];
    if (auto dateInput = dynamic_pointer_cast<DateInput>(baseInputElementCpp))
        return [[ACSDateInput alloc] initWithDateInput:dateInput];
    if (auto choiceSetInput = dynamic_pointer_cast<ChoiceSetInput>(baseInputElementCpp))
        return [[ACSChoiceSetInput alloc] initWithChoiceSetInput:choiceSetInput];
    if (auto timeInput = dynamic_pointer_cast<TimeInput>(baseInputElementCpp))
        return [[ACSTimeInput alloc] initWithTimeInput:timeInput];
    if (auto numberInput = dynamic_pointer_cast<NumberInput>(baseInputElementCpp))
        return [[ACSNumberInput alloc] initWithNumberInput:numberInput];
    
    // Can't downcast any further. Returning as ACSBaseElement.
    return [[ACSBaseInputElement alloc] initWithBaseInputElement:baseInputElementCpp];
}

+ (ACSCollectionTypeElement *)covertFromCollectionTypeElement:(std::shared_ptr<CollectionTypeElement>)collectionTypeElementCpp
{
    if (auto column = dynamic_pointer_cast<Column>(collectionTypeElementCpp))
        return [[ACSColumn alloc] initWithColumn:column];
    if (auto columnSet = dynamic_pointer_cast<ColumnSet>(collectionTypeElementCpp))
        return [[ACSColumnSet alloc] initWithColumnSet:columnSet];
    if (auto container = dynamic_pointer_cast<Container>(collectionTypeElementCpp))
        return [[ACSContainer alloc] initWithContainer:container];
    
    // Can't downcast any further. Returning as ACSBaseElement.
    return [[ACSCollectionTypeElement alloc] initWithCollectionTypeElement:collectionTypeElementCpp];
}

@end
