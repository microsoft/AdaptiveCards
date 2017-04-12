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
        m_body = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
        if (m_body == nullptr)
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

        return GenerateContainedElementsProjection(m_sharedAdaptiveCard->GetBody(), m_body.Get());
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_Version(HSTRING* version)
    {
        return UTF8ToHString(m_sharedAdaptiveCard->GetVersion(), version);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_Version(HSTRING version)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(version, out));
        m_sharedAdaptiveCard->SetVersion(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_MinVersion(HSTRING* minVersion)
    {
        return UTF8ToHString(m_sharedAdaptiveCard->GetMinVersion(), minVersion);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_MinVersion(HSTRING minVersion)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(minVersion, out));
        m_sharedAdaptiveCard->SetMinVersion(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_FallbackText(HSTRING* fallbackText)
    {
        return UTF8ToHString(m_sharedAdaptiveCard->GetFallbackText(), fallbackText);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::put_FallbackText(HSTRING fallbackText)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(fallbackText, out));
        m_sharedAdaptiveCard->SetFallbackText(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_Body(IVector<IAdaptiveCardElement*>** body)
    {
        return m_body.CopyTo(body);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCard::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::AdaptiveCard;
        return S_OK;
    }
}}