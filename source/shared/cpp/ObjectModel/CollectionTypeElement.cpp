#include "pch.h"
#include "CollectionTypeElement.h"
#include "Util.h"

using namespace AdaptiveSharedNamespace;

CollectionTypeElement::CollectionTypeElement(CardElementType type, ContainerStyle style, 
    VerticalContentAlignment alignment) : BaseCardElement(type), m_style(style), 
    m_verticalContentAlignment(alignment), m_hasPadding(false), m_hasBleed(false), m_parentalId()
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
    if(GetStyle() != ContainerStyle::None) 
    {
        if(context.GetParentalContainerStyle() != GetStyle())
        {
            if(context.GetParentalContainerStyle() == ContainerStyle::None &&
                GetStyle() == ContainerStyle::Default)
            {
                SetPadding(false);
                return;
            }

            SetPadding(true);
            return;
        }
    }

    SetPadding(false);
}

bool CollectionTypeElement::GetBleed(void) const
{
    return m_hasBleed;
}

void CollectionTypeElement::SetBleed(const bool value)
{
    m_hasBleed = value;
}

// Applies Padding Flag When appropriate
void CollectionTypeElement::ConfigBleed(const ParseContext& context)
{
    // we allows bleed when self has padding and at least one parent has padding
    AdaptiveSharedNamespace::InternalId id = context.GetIDOfParentWithPadding();
    bool canBleed = GetBleed() && (id != AdaptiveSharedNamespace::InternalId::Invalid);
    if(canBleed)
    {
        SetParentalId(id);
    }
    SetCanBleed(canBleed);
}

void CollectionTypeElement::SetCanBleed(const bool value)
{
    m_canBleed = value;
}

bool CollectionTypeElement::GetCanBleed() const
{
    return m_canBleed;
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
