// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "StyledCollectionElement.h"
#include "Util.h"

using namespace AdaptiveCards;

StyledCollectionElement::StyledCollectionElement(CardElementType type, ContainerStyle style, std::optional<VerticalContentAlignment> alignment) :
    CollectionCoreElement(type), m_style(style), m_verticalContentAlignment(alignment),
    m_bleedDirection(ContainerBleedDirection::BleedAll), m_minHeight(0), m_hasPadding(false), m_hasBleed(false), m_parentalId()
{
}

ContainerStyle StyledCollectionElement::GetStyle() const
{
    return m_style;
}

void StyledCollectionElement::SetStyle(const ContainerStyle value)
{
    m_style = value;
}

std::optional<VerticalContentAlignment> StyledCollectionElement::GetVerticalContentAlignment() const
{
    return m_verticalContentAlignment;
}

void StyledCollectionElement::SetVerticalContentAlignment(const std::optional<VerticalContentAlignment> value)
{
    m_verticalContentAlignment = value;
}

bool StyledCollectionElement::GetPadding() const
{
    return m_hasPadding;
}

void StyledCollectionElement::SetPadding(const bool value)
{
    m_hasPadding = value;
}

// Applies Padding Flag When appropriate
void StyledCollectionElement::ConfigPadding(const ParseContext& context)
{
    // We set padding when child's style is set explicitly (not None) and is different than the parental style
    const bool padding = (GetStyle() != ContainerStyle::None) && (context.GetParentalContainerStyle() != GetStyle());
    SetPadding(padding);
}

bool StyledCollectionElement::GetBleed() const
{
    return m_hasBleed;
}

void StyledCollectionElement::SetBleed(const bool value)
{
    m_hasBleed = value;
}

// Applies Bleed Flag When appropriate
void StyledCollectionElement::ConfigBleed(const AdaptiveCards::ParseContext& context)
{
    // We allow bleed when the current container has padding and bleed set, and when the parents don't impose a
    // restiction via bleed direction
    const AdaptiveCards::InternalId id = context.PaddingParentInternalId();
    const bool canBleed = GetPadding() && GetBleed();
    if (canBleed && context.GetBleedDirection() != ContainerBleedDirection::BleedRestricted)
    {
        SetParentalId(id);
        SetBleedDirection(context.GetBleedDirection());
    }
    else
    {
        SetBleedDirection(ContainerBleedDirection::BleedRestricted);
    }
}

void StyledCollectionElement::SetParentalId(const AdaptiveCards::InternalId& id)
{
    m_parentalId = id;
}

AdaptiveCards::InternalId StyledCollectionElement::GetParentalId(void) const
{
    return m_parentalId;
}

// convinience method for configuring for container style
void StyledCollectionElement::ConfigForContainerStyle(const ParseContext& context)
{
    ConfigPadding(context);
    ConfigBleed(context);
}

std::shared_ptr<BackgroundImage> StyledCollectionElement::GetBackgroundImage() const
{
    return m_backgroundImage;
}

void StyledCollectionElement::SetBackgroundImage(const std::shared_ptr<BackgroundImage> value)
{
    m_backgroundImage = value;
}

unsigned int StyledCollectionElement::GetMinHeight() const
{
    return m_minHeight;
}

void StyledCollectionElement::SetMinHeight(const unsigned int value)
{
    m_minHeight = value;
}

std::shared_ptr<BaseActionElement> StyledCollectionElement::GetSelectAction() const
{
    return m_selectAction;
}

void StyledCollectionElement::SetSelectAction(const std::shared_ptr<BaseActionElement> action)
{
    m_selectAction = action;
}

Json::Value StyledCollectionElement::SerializeToJsonValue() const
{
    Json::Value root = CollectionCoreElement::SerializeToJsonValue();

    if (m_selectAction != nullptr)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] =
            BaseCardElement::SerializeSelectAction(m_selectAction);
    }

    if (m_backgroundImage != nullptr && !m_backgroundImage->GetUrl().empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::BackgroundImage)] = m_backgroundImage->SerializeToJsonValue();
    }

    if (GetStyle() != ContainerStyle::None)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ContainerStyleToString(GetStyle());
    }

    if (GetVerticalContentAlignment().has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalContentAlignment)] =
            VerticalContentAlignmentToString(GetVerticalContentAlignment().value_or(VerticalContentAlignment::Top));
    }

    if (GetBleed())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Bleed)] = true;
    }

    if (m_minHeight)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MinHeight)] = std::to_string(GetMinHeight()) + "px";
    }

    return root;
}
