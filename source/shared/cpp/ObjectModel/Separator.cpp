// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Separator.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

Separator::Separator() : m_thickness(SeparatorThickness::Default), m_color(ForegroundColor::Default)
{
}

std::shared_ptr<Separator> Separator::Deserialize(const Json::Value& json)
{
    std::shared_ptr<Separator> separator = std::make_shared<Separator>();

    separator->SetColor(
        ParseUtil::GetEnumValue<ForegroundColor>(json, AdaptiveCardSchemaKey::Color, ForegroundColor::Default, ForegroundColorFromString));
    separator->SetThickness(ParseUtil::GetEnumValue<SeparatorThickness>(
        json, AdaptiveCardSchemaKey::Thickness, SeparatorThickness::Default, SeparatorThicknessFromString));

    return separator;
}

std::shared_ptr<Separator> Separator::DeserializeFromString(const std::string& jsonString)
{
    return Separator::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string Separator::Serialize()
{
    return ParseUtil::JsonToString(SerializeToJsonValue());
}

Json::Value Separator::SerializeToJsonValue()
{
    Json::Value root;
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Color)] = ForegroundColorToString(GetColor());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Thickness)] = SeparatorThicknessToString(GetThickness());

    return root;
}

ForegroundColor Separator::GetColor() const
{
    return m_color;
}

void Separator::SetColor(const ForegroundColor value)
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
