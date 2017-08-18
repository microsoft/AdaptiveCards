#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"

namespace AdaptiveCards
{
class Separator
{
public:
    Separator();

    std::string Serialize();
    Json::Value SerializeToJsonValue();

    SeparatorThickness GetThickness() const;
    void SetThickness(SeparatorThickness value);

    AdaptiveColor GetColor() const;
    void SetColor(const AdaptiveColor value);

    static std::shared_ptr<Separator> Deserialize(const Json::Value& root);
    static std::shared_ptr<Separator> DeserializeFromString(const std::string& jsonString);

private:
    SeparatorThickness m_thickness;
    AdaptiveColor m_color;
};
}
