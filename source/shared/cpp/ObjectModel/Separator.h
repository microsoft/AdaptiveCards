// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"

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

    ForegroundColor GetColor() const;
    void SetColor(const ForegroundColor value);

    static std::shared_ptr<Separator> Deserialize(const Json::Value& root);
    static std::shared_ptr<Separator> DeserializeFromString(const std::string& jsonString);

private:
    SeparatorThickness m_thickness;
    ForegroundColor m_color;
};
} // namespace AdaptiveCards
