#include "pch.h"
#include "Height.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

Height::Height() : m_heightType(HeightType::Auto) { }

Height::Height(HeightType heightType) : m_heightType(heightType) { }

HeightType Height::GetHeightType()
{
    return m_heightType;
}

void Height::SetHeightType(HeightType value)
{
    m_heightType = value;
}

Height Height::Deserialize(
    const Json::Value& json)
{
    HeightType heightType = ParseUtil::GetEnumValue<HeightType>(json, AdaptiveCardSchemaKey::Height, HeightType::Auto, HeightTypeFromString, false /* isRequired */);
    Height height(heightType);
    return height;
}

std::shared_ptr<Height> Height::DeserializeFromString(
    const std::string& jsonString)
{
    return std::make_shared<Height>(Height::Deserialize(ParseUtil::GetJsonValueFromString(jsonString)));
}

std::string Height::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value Height::SerializeToJsonValue()
{
    Json::Value root;
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Height)] = HeightTypeToString(GetHeightType());

    return root;
}