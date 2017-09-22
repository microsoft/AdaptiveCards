#include "pch.h"
#include "AdaptiveRenderResult.h"

#include "AdaptiveCard.h"
#include "AsyncOperations.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>
#include "XamlBuilder.h"
#include "XamlHelpers.h"
#include "AdaptiveHostConfig.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    AdaptiveRenderResult::AdaptiveRenderResult()
    {
    }

    HRESULT AdaptiveRenderResult::RuntimeClassInitialize()
    {
        return S_OK;
    }

    HRESULT AdaptiveRenderResult::RuntimeClassInitialize(
        bool isValid,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* card,
        ABI::Windows::UI::Xaml::IUIElement* uiElement,
        std::shared_ptr<std::vector<InputItem>> inputs)
    {
        m_isValid = isValid;
        m_card = card;
        m_uiElement = uiElement;
        m_inputs = inputs;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderResult::get_Card(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard** value)
    {
        return m_card.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderResult::get_UI(ABI::Windows::UI::Xaml::IUIElement** value)
    {
        return m_uiElement.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderResult::get_InputValuesJson(HSTRING* value)
    {
        HSTRING inputsJson = SerializeInputItems(*m_inputs);
        *value = inputsJson;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRenderResult::IsValid(boolean* value)
    {
        *value = m_isValid;
        return S_OK;
    }

}}