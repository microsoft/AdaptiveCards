#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"

namespace AdaptiveCards
{
struct Height
{
    // Height is a struct rather than an enum since in the future it's possible that we'll have
    // heights of pixel heights, or star-based heights. So following a similar pattern to XAML GridLength.
    HeightType heightType = HeightType::Auto;

    static Height Deserialize(const Json::Value& json, const Height& defaultValue);
    static std::string SerializeToString(const Height& defaultValue);
};
}