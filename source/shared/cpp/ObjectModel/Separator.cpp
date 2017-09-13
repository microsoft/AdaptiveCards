#include "Separator.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

Separator::Separator()
{
}


std::shared_ptr<Separator> Separator::Deserialize(const Json::Value& json)
{
    std::shared_ptr<Separator> separator = std::make_shared<Separator>();

    separator->SetColor(ParseUtil::GetEnumValue<Color>(json, AdaptiveCardSchemaKey::Color, Color::Default, ColorFromString));
    separator->SetThickness(ParseUtil::GetEnumValue<SeparatorThickness>(json, AdaptiveCardSchemaKey::Thickness, SeparatorThickness::Default, SeparatorThicknessFromString));

    return separator;
}

std::shared_ptr<Separator> Separator::DeserializeFromString(const std::string& jsonString)
{
    return Separator::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string Separator::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value Separator::SerializeToJsonValue()
{
    Json::Value root;
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Color)] = ColorToString(GetColor());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Thickness)] = SeparatorThicknessToString(GetThickness());

    return root;
}

Color Separator::GetColor() const
{
    return m_color;
}

void Separator::SetColor(const Color value)
{
    m_color = value;
}

SeparatorThickness Separator::GetThickness() const
{
    return m_thickness;
}

void Separator::SetThickness(const SeparatorThickness value)
{
    m_thickness = value;
}