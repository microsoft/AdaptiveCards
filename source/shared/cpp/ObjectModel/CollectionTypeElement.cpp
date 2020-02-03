// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "CollectionTypeElement.h"
#include "Util.h"

using namespace AdaptiveSharedNamespace;

CollectionTypeElement::CollectionTypeElement(CardElementType type, ContainerStyle style, VerticalContentAlignment alignment) :
    BaseCardElement(type), m_style(style), m_verticalContentAlignment(alignment),
    m_bleedDirection(ContainerBleedDirection::BleedAll), m_minHeight(0), m_hasPadding(false), m_hasBleed(false), m_parentalId()
{
}

ContainerStyle CollectionTypeElement::GetStyle() const
{
    return m_style;
}

void CollectionTypeElement::SetStyle(const ContainerStyle value)
{
    m_style = value;
}

VerticalContentAlignment CollectionTypeElement::GetVerticalContentAlignment() const
{
    return m_verticalContentAlignment;
}

void CollectionTypeElement::SetVerticalContentAlignment(const VerticalContentAlignment value)
{
    m_verticalContentAlignment = value;
}

bool CollectionTypeElement::GetPadding() const
{
    return m_hasPadding;
}

void CollectionTypeElement::SetPadding(const bool value)
{
    m_hasPadding = value;
}

// Applies Padding Flag When appropriate
void CollectionTypeElement::ConfigPadding(const ParseContext& context)
{
    // We set padding when child's style is set explicitly (not None) and is different than the parental style
    const bool padding = (GetStyle() != ContainerStyle::None) && (context.GetParentalContainerStyle() != GetStyle());
    SetPadding(padding);
}

bool CollectionTypeElement::GetBleed() const
{
    return m_hasBleed;
}

void CollectionTypeElement::SetBleed(const bool value)
{
    m_hasBleed = value;
}

// Applies Bleed Flag When appropriate
void CollectionTypeElement::ConfigBleed(const AdaptiveCards::ParseContext& context)
{
    // We allow bleed when the current container has padding and bleed set, and when the parents don't impose a
    // restiction via bleed direction
    const AdaptiveSharedNamespace::InternalId id = context.PaddingParentInternalId();
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

void CollectionTypeElement::SetParentalId(const AdaptiveSharedNamespace::InternalId& id)
{
    m_parentalId = id;
}

AdaptiveSharedNamespace::InternalId CollectionTypeElement::GetParentalId(void) const
{
    return m_parentalId;
}

// convinience method for configuring for container style
void CollectionTypeElement::ConfigForContainerStyle(const ParseContext& context)
{
    ConfigPadding(context);
    ConfigBleed(context);
}

std::shared_ptr<BackgroundImage> CollectionTypeElement::GetBackgroundImage() const
{
    return m_backgroundImage;
}

void CollectionTypeElement::SetBackgroundImage(const std::shared_ptr<BackgroundImage> value)
{
    m_backgroundImage = value;
}

unsigned int CollectionTypeElement::GetMinHeight() const
{
    return m_minHeight;
}

void CollectionTypeElement::SetMinHeight(const unsigned int value)
{
    m_minHeight = value;
}

std::shared_ptr<BaseActionElement> CollectionTypeElement::GetSelectAction() const
{
    return m_selectAction;
}

void CollectionTypeElement::SetSelectAction(const std::shared_ptr<BaseActionElement> action)
{
    m_selectAction = action;
}

Json::Value CollectionTypeElement::SerializeToJsonValue() const
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

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

    if (GetVerticalContentAlignment() != VerticalContentAlignment::Top)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalContentAlignment)] =
            VerticalContentAlignmentToString(GetVerticalContentAlignment());
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
