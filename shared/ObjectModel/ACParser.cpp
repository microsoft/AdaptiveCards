#include "ACParser.h"
#include "ACParseException.h"

namespace AdaptiveCards
{

void ACParser::ThrowIfNotJsonObject(const Json::Value& json)
{
    if (!json.isObject()) {
        throw ACParseException("Expected JSON Object\n");
    }
}

void ACParser::ExpectString(const Json::Value& json)
{
    if (!json.isString())
    {
        throw ACParseException("The JSON element did not have the expected type 'string'");
    }
}

std::string ACParser::GetTypeAsString(const Json::Value& json)
{
    std::string typeKey = "@type";
    if (!json.isMember(typeKey))
    {
        throw ACParseException("The JSON element is missing the following value: " + typeKey);
    }

    return json.get(typeKey, Json::Value()).asString();
}

std::string ACParser::GetString(const Json::Value& json, AdaptiveCardSchemaKey key)
{
    std::string propertyName = AdaptiveCardSchemaKeyToString(key);
    auto propertyValue = json.get(propertyName, Json::Value());
    if (propertyValue.empty())
    {
        return "";
    }

    if (!propertyValue.isString())
    {
        throw ACParseException("Value was invalid. Expected type string.");
    }

    return propertyValue.asString();
}

void ACParser::ExpectTypeString(const Json::Value& json, CardElementType bodyType)
{
    std::string actualType = GetTypeAsString(json);
    std::string expectedTypeStr = CardElementTypeToString(bodyType);
    bool isTypeCorrect = expectedTypeStr.compare(actualType) == 0;
    if (!isTypeCorrect)
    {
        throw ACParseException("The JSON element did not have the correct type. Expected: " + expectedTypeStr + ", Actual: " + actualType);
    }
}

// throws if the key is missing or the value mapped to the key is the wrong type
void ACParser::ExpectKeyAndValueType(const Json::Value& json, const char* expectedKey, std::function<void(const Json::Value&)> throwIfWrongType)
{
    if (expectedKey == nullptr)
    {
        throw ACParseException("null expectedKey");
    }

    if (!json.isMember(expectedKey))
    {
        throw ACParseException("The JSON element is missing the following key: " + std::string(expectedKey));
    }

    auto value = json.get(expectedKey, Json::Value());
    throwIfWrongType(value);
}

CardElementType ACParser::GetCardElementType(const Json::Value& json)
{
    std::string actualType = GetTypeAsString(json);
    try
    {
        return CardElementTypeFromString(actualType);
    }
    catch (const std::out_of_range&)
    {
        throw ACParseException("Invalid CardElementType");
    }
}

ACParser::ACParser()
{
}

ACParser::~ACParser()
{
}

}