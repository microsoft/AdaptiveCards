// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "BackgroundImage.h"
#include "ParseContext.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

std::string BackgroundImage::GetUrl() const { return m_url; }

void BackgroundImage::SetUrl(const std::string& value) { m_url = value; }

ImageFillMode BackgroundImage::GetFillMode() const { return m_fillMode; }

void BackgroundImage::SetFillMode(const ImageFillMode& value) { m_fillMode = value; }

HorizontalAlignment BackgroundImage::GetHorizontalAlignment() const { return m_hAlignment; }

void BackgroundImage::SetHorizontalAlignment(const HorizontalAlignment& value) { m_hAlignment = value; }

VerticalAlignment BackgroundImage::GetVerticalAlignment() const { return m_vAlignment; }

void BackgroundImage::SetVerticalAlignment(const VerticalAlignment& value) { m_vAlignment = value; }

std::string BackgroundImage::Serialize() const
{
    return ParseUtil::JsonToString(SerializeToJsonValue());
}

Json::Value BackgroundImage::SerializeToJsonValue() const
{
    Json::Value root;

    // if BackgroundImage has a url and the rest as default values
    if (!m_url.empty() && m_fillMode == ImageFillMode::Cover && m_hAlignment == HorizontalAlignment::Left &&
        m_vAlignment == VerticalAlignment::Top)
    {
        root = m_url;
    }

    // standard serialization process
    else
    {
        if (!m_url.empty())
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Url)] = m_url;
        }

        if (m_fillMode != ImageFillMode::Cover)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FillMode)] =
                ImageFillModeToString(m_fillMode);
        }

        if (m_hAlignment != HorizontalAlignment::Left)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment)] =
                HorizontalAlignmentToString(m_hAlignment);
        }

        if (m_vAlignment != VerticalAlignment::Top)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalAlignment)] =
                VerticalAlignmentToString(m_vAlignment);
        }
    }
    return root;
}

std::shared_ptr<BackgroundImage> BackgroundImage::Deserialize(const Json::Value& json)
{
    std::shared_ptr<BackgroundImage> image = std::make_shared<BackgroundImage>();

    image->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, true));

    image->SetFillMode(ParseUtil::GetEnumValue<ImageFillMode>(
        json, AdaptiveCardSchemaKey::FillMode, ImageFillMode::Cover, ImageFillModeFromString));

    image->SetHorizontalAlignment(ParseUtil::GetEnumValue<HorizontalAlignment>(
        json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString));

    image->SetVerticalAlignment(ParseUtil::GetEnumValue<VerticalAlignment>(
        json, AdaptiveCardSchemaKey::VerticalAlignment, VerticalAlignment::Top, VerticalAlignmentFromString));

    return image;
}

std::shared_ptr<BackgroundImage> BackgroundImage::DeserializeFromString(const std::string& jsonString)
{
    return BackgroundImage::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}
