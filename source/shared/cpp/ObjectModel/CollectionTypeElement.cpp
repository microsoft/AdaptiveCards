#include "pch.h"
#include "CollectionTypeElement.h"
#include "Util.h"

using namespace AdaptiveSharedNamespace;

CollectionTypeElement::CollectionTypeElement(CardElementType type, ContainerStyle style, VerticalContentAlignment alignment) :
    BaseCardElement(type), m_style(style), m_verticalContentAlignment(alignment), m_hasPadding(false), m_hasBleed(false),
    m_parentalId(), m_canBleed(false), m_bleedDirection(ContainerBleedDirection::BleedToBothEdges)
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
    // we set padding when parental style is different from child's, and its style should not be None
    if ((GetStyle() != ContainerStyle::None) && (context.GetParentalContainerStyle() != GetStyle()) &&
        (context.GetParentalContainerStyle() != ContainerStyle::NotSet))
    {
        SetPadding(!(context.GetParentalContainerStyle() == ContainerStyle::None &&
            GetStyle() == ContainerStyle::Default));
    } 
    else 
    {
        SetPadding(false);
    }
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
    // we allows bleed when self has padding and at least one parent has padding
    const AdaptiveSharedNamespace::InternalId id = context.PaddingParentInternalId();
    const bool canBleed = GetPadding() && GetBleed();
    if (canBleed && context.GetBleedDirection() != ContainerBleedDirection::BleedRestricted)
    {
        SetParentalId(id);
        SetCanBleed(true);
    }
    else
    { 
        SetCanBleed(false);
    }
    SetBleedDirection(context.GetBleedDirection());
}

void CollectionTypeElement::SetParentalId(const AdaptiveSharedNamespace::InternalId &id)
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

    return root;
}
