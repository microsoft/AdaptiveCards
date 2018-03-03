#include <iomanip>
#include <regex>
#include <iostream>
#include <codecvt>
#include "CustomObjectDelegateForIOS.h"
#include "DateTimePreparser.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

CustomObjectDelegateForIOS::CustomObjectDelegateForIOS() :
    BaseCardElement(CardElementType::CustomIOSDelegate)
{
    PopulateKnownPropertiesSet();
}

CustomObjectDelegateForIOS::CustomObjectDelegateForIOS(
    Json::Value const &paylaod) :
    BaseCardElement(CardElementType::CustomIOSDelegate),
    m_payload(paylaod)
{
    PopulateKnownPropertiesSet();
}

Json::Value CustomObjectDelegateForIOS::SerializeToJsonValue()
{
    return GetJsonPayload();
}

Json::Value CustomObjectDelegateForIOS::GetJsonPayload()
{
    return m_payload;
}

void CustomObjectDelegateForIOS::SetJsonPayload(const Json::Value& payload)
{
    m_payload = payload;
}

void CustomObjectDelegateForIOS::PopulateKnownPropertiesSet() 
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Payload));
}

std::shared_ptr<BaseCardElement> CustomObjectDelegateForIOSParser::Deserialize(
    std::shared_ptr<ElementParserRegistration>,
    std::shared_ptr<ActionParserRegistration>,
    const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::CustomIOSDelegate);

    auto payload = ParseUtil::ExtractJsonValue(json, AdaptiveCardSchemaKey::Payload, true);
    std::shared_ptr<CustomObjectDelegateForIOS> customObject = std::make_shared<CustomObjectDelegateForIOS>(payload);

    return customObject;
}

std::shared_ptr<BaseCardElement> CustomObjectDelegateForIOSParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return CustomObjectDelegateForIOSParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}
