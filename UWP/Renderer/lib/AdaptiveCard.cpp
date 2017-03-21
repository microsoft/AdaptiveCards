#include "pch.h"
#include "AdaptiveCard.h"

#include <json.h>
#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    _Use_decl_annotations_
    HRESULT AdaptiveCardStaticsImpl::CreateCardFromJson(HSTRING adaptiveJson, IAdaptiveCard** card) noexcept try
    {
        *card = nullptr;

        std::string adaptiveJsonString;
        RETURN_IF_FAILED(HStringToUTF8(adaptiveJson, adaptiveJsonString));

        Json::Value adaptiveJsonRoot;
        Json::Reader jsonRreader;
        bool parsingSuccessful = jsonRreader.parse(adaptiveJsonString, adaptiveJsonRoot);
        if (!parsingSuccessful)
        {
            return E_FAIL;
        }

        std::shared_ptr<::AdaptiveCards::AdaptiveCard> sharedAdaptiveCard = ::AdaptiveCards::AdaptiveCard::Deserialize(adaptiveJsonRoot);
        return MakeAndInitialize<AdaptiveCard>(card, sharedAdaptiveCard);
    } CATCH_RETURN;

    HRESULT AdaptiveCard::RuntimeClassInitialize()
    {
        m_size = ABI::AdaptiveCards::XamlCardRenderer::CardElementSize::Auto;

        m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
        if (m_items == nullptr)
        {
            return E_FAIL;
        }
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::RuntimeClassInitialize(std::shared_ptr<::AdaptiveCards::AdaptiveCard> sharedAdaptiveCard)
    {
        RETURN_IF_FAILED(RuntimeClassInitialize());
        m_sharedAdaptiveCard = sharedAdaptiveCard;

        return GenerateProjectionOfContainedElements(m_sharedAdaptiveCard->GetBody()->GetItems(),
            m_items.Get());
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_Items(IVector<IAdaptiveCardElement*>** items)
    {
        return m_items.CopyTo(items);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_ElementType(ElementType* /*elementType*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_ElementType(ElementType /*elementType*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_Size(ABI::AdaptiveCards::XamlCardRenderer::CardElementSize* size)
    {
        *size = m_size;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_Size(ABI::AdaptiveCards::XamlCardRenderer::CardElementSize size)
    {
        m_size = size;
        return S_OK;
    }
}}