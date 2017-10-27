#include "pch.h"
#include "CustomElementWrapper.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Uwp;

namespace AdaptiveCards { namespace Uwp
{

bool CustomElementWrapper::GetSeparator() const
{
    ComPtr<IAdaptiveCardElement> cardElement;
    m_cardElement.As(&cardElement);

    boolean hasSeparator;
    THROW_IF_FAILED(cardElement->get_Separator(&hasSeparator));
    return hasSeparator;
}

void CustomElementWrapper::SetSeparator(const bool value)
{
    ComPtr<IAdaptiveCardElement> cardElement;
    m_cardElement.As(&cardElement);

    THROW_IF_FAILED(cardElement->put_Separator(value));
}

Spacing CustomElementWrapper::GetSpacing() const
{
    ComPtr<IAdaptiveCardElement> cardElement;
    m_cardElement.As(&cardElement);

    ABI::AdaptiveCards::Uwp::Spacing spacing;
    THROW_IF_FAILED(cardElement->get_Spacing(&spacing));

    return static_cast<Spacing> (spacing);
}

void CustomElementWrapper::SetSpacing(const Spacing value)
{
    ComPtr<IAdaptiveCardElement> cardElement;
    m_cardElement.As(&cardElement);

    THROW_IF_FAILED(cardElement->put_Spacing(static_cast<ABI::AdaptiveCards::Uwp::Spacing>(value)));
}

std::string CustomElementWrapper::GetId() const
{
    ComPtr<IAdaptiveCardElement> cardElement;
    m_cardElement.As(&cardElement);

    Wrappers::HString id; 
    THROW_IF_FAILED(cardElement->get_Id(id.GetAddressOf()));
    return HStringToUTF8(id.Get());
}

void CustomElementWrapper::SetId(const std::string value)
{
    ComPtr<IAdaptiveCardElement> cardElement;
    m_cardElement.As(&cardElement);

    Wrappers::HString id; 
    THROW_IF_FAILED(UTF8ToHString(value, id.GetAddressOf()));
    THROW_IF_FAILED(cardElement->put_Id(id.Get()));
}

std::string CustomElementWrapper::Serialize()
{
    throw std::logic_error("Serialize not implemented for custom elements");
}

HRESULT CustomElementWrapper::GetWrappedElement(ABI::AdaptiveCards::Uwp::IAdaptiveCardElement** cardElement)
{
    return m_cardElement.CopyTo(cardElement);
}
}}
