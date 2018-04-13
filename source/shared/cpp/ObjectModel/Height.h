#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"

AdaptiveSharedNamespaceStart
class Height
{
public:
    Height();
    Height(HeightType heightType);

    HeightType GetHeightType();
    void SetHeightType(HeightType value);

    std::string Serialize();

    Json::Value SerializeToJsonValue();

    static Height Deserialize(
        const Json::Value& root);

    static std::shared_ptr<Height> DeserializeFromString(
        const std::string& jsonString);

private:
    // Height is a struct rather than an enum since in the future it's possible that we'll have
    // heights of pixel heights, or star-based heights. So following a similar pattern to XAML GridLength.
    HeightType m_heightType;
};
AdaptiveSharedNamespaceEnd