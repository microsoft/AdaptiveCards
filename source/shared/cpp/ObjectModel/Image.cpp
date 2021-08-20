// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Image.h"
#include "ParseUtil.h"
#include "ParseContext.h"
#include "Util.h"

using namespace AdaptiveCards;

Image::Image() :
    BaseCardElement(CardElementType::Image), m_imageStyle(ImageStyle::Default), m_imageSize(ImageSize::None),
    m_pixelWidth(0), m_pixelHeight(0), m_hAlignment(std::nullopt)
{
    PopulateKnownPropertiesSet();
}

Json::Value Image::SerializeToJsonValue() const
{
    const std::string pixelstring("px");

    Json::Value root = BaseCardElement::SerializeToJsonValue();

    if (m_pixelWidth || m_pixelHeight)
    {
        if (m_pixelWidth)
        {
            std::ostringstream stringStream;
            stringStream << m_pixelWidth;

            std::string widthString = stringStream.str() + pixelstring;
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Width)] = widthString;
        }
        if (m_pixelHeight)
        {
            std::ostringstream stringStream;
            stringStream << m_pixelHeight;

            std::string heightString = stringStream.str() + pixelstring;
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Height)] = heightString;
        }
    }
    else if (m_imageSize != ImageSize::None)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Size)] = ImageSizeToString(m_imageSize);
    }

    if (m_imageStyle != ImageStyle::Default)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ImageStyleToString(m_imageStyle);
    }

    if (!m_url.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Url)] = m_url;
    }

    if (!m_backgroundColor.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::BackgroundColor)] = m_backgroundColor;
    }

    if (m_hAlignment.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment)] =
            HorizontalAlignmentToString(m_hAlignment.value_or(HorizontalAlignment::Left));
    }

    if (!m_altText.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::AltText)] = m_altText;
    }

    if (m_selectAction != nullptr)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] =
            BaseCardElement::SerializeSelectAction(m_selectAction);
    }

    return root;
}

std::string Image::GetUrl() const
{
    return m_url;
}

void Image::SetUrl(const std::string& value)
{
    m_url = value;
}

std::string Image::GetBackgroundColor() const
{
    return m_backgroundColor;
}

void Image::SetBackgroundColor(const std::string& value)
{
    m_backgroundColor = value;
}

ImageStyle Image::GetImageStyle() const
{
    return m_imageStyle;
}

void Image::SetImageStyle(const ImageStyle value)
{
    m_imageStyle = value;
}

ImageSize Image::GetImageSize() const
{
    return m_imageSize;
}

void Image::SetImageSize(const ImageSize value)
{
    m_imageSize = value;
}

std::string Image::GetAltText() const
{
    return m_altText;
}

void Image::SetAltText(const std::string& value)
{
    m_altText = value;
}

std::optional<HorizontalAlignment> Image::GetHorizontalAlignment() const
{
    return m_hAlignment;
}

void Image::SetHorizontalAlignment(const std::optional<HorizontalAlignment> value)
{
    m_hAlignment = value;
}

std::shared_ptr<BaseActionElement> Image::GetSelectAction() const
{
    return m_selectAction;
}

void Image::SetSelectAction(const std::shared_ptr<BaseActionElement> action)
{
    m_selectAction = action;
}

unsigned int Image::GetPixelWidth() const
{
    return m_pixelWidth;
}

void Image::SetPixelWidth(unsigned int value)
{
    m_pixelWidth = value;
}

unsigned int Image::GetPixelHeight() const
{
    return m_pixelHeight;
}

void Image::SetPixelHeight(unsigned int value)
{
    m_pixelHeight = value;
}

std::shared_ptr<BaseCardElement> ImageParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ImageParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

std::shared_ptr<BaseCardElement> ImageParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::Image);
    return ImageParser::DeserializeWithoutCheckingType(context, json);
}

std::shared_ptr<BaseCardElement> ImageParser::DeserializeWithoutCheckingType(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<Image> image = BaseCardElement::Deserialize<Image>(context, json);

    image->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, true));
    image->SetBackgroundColor(ValidateColor(ParseUtil::GetString(json, AdaptiveCardSchemaKey::BackgroundColor), context.warnings));
    image->SetImageStyle(ParseUtil::GetEnumValue<ImageStyle>(json, AdaptiveCardSchemaKey::Style, ImageStyle::Default, ImageStyleFromString));
    image->SetAltText(ParseUtil::GetString(json, AdaptiveCardSchemaKey::AltText));
    image->SetHorizontalAlignment(ParseUtil::GetOptionalEnumValue<HorizontalAlignment>(
        json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignmentFromString));

    const auto& widthDimension =
        ParseSizeForPixelSize(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Width), &context.warnings);
    const auto& heightDimension =
        ParseSizeForPixelSize(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Height), &context.warnings);

    if (widthDimension.has_value() || heightDimension.has_value())
    {
        // Need to take breaking change to only set width/height if parse was successful (see microsoft/AdaptiveCards#5781)
        image->SetPixelWidth(widthDimension.value_or(0));
        image->SetPixelHeight(heightDimension.value_or(0));
    }
    else
    {
        image->SetImageSize(ParseUtil::GetEnumValue<ImageSize>(json, AdaptiveCardSchemaKey::Size, ImageSize::None, ImageSizeFromString));
    }

    // Parse optional selectAction
    image->SetSelectAction(ParseUtil::GetAction(context, json, AdaptiveCardSchemaKey::SelectAction, false));
    return image;
}

void Image::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::AltText),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::BackgroundColor),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Height),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Size),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Url),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Width)});
}

void Image::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    RemoteResourceInformation imageResourceInfo;
    imageResourceInfo.url = GetUrl();
    imageResourceInfo.mimeType = "image";
    resourceInfo.push_back(imageResourceInfo);
}
