#include "pch.h"
#include "RenderedAdaptiveCard.h"

#include "AdaptiveCard.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>
#include "XamlBuilder.h"
#include "XamlHelpers.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveActionEventArgs.h"
#include "AdaptiveMediaEventArgs.h"
#include "AdaptiveError.h"
#include "vector.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    RenderedAdaptiveCard::RenderedAdaptiveCard() {}

    HRESULT RenderedAdaptiveCard::RuntimeClassInitialize()
    {
        RETURN_IF_FAILED(
            RenderedAdaptiveCard::RuntimeClassInitialize(Make<Vector<ABI::AdaptiveNamespace::AdaptiveError*>>().Get(),
                                                         Make<Vector<ABI::AdaptiveNamespace::AdaptiveWarning*>>().Get()));
        return S_OK;
    }

    HRESULT RenderedAdaptiveCard::RuntimeClassInitialize(
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveError*>* errors,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* warnings)
    {
        m_errors = errors;
        m_warnings = warnings;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveNamespace::AdaptiveInputs>(&m_inputs));
        m_actionEvents = std::make_shared<ActionEventSource>();
        m_mediaClickedEvents = std::make_shared<MediaEventSource>();
        return S_OK;
    }

    HRESULT RenderedAdaptiveCard::get_OriginatingCard(_COM_Outptr_ IAdaptiveCard** value)
    {
        return m_originatingCard.CopyTo(value);
    }

    HRESULT RenderedAdaptiveCard::get_FrameworkElement(_COM_Outptr_ IFrameworkElement** value)
    {
        return m_frameworkElement.CopyTo(value);
    }

    HRESULT RenderedAdaptiveCard::get_UserInputs(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputs** value)
    {
        return m_inputs.CopyTo(value);
    }

    HRESULT RenderedAdaptiveCard::add_Action(
        _In_ ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveNamespace::RenderedAdaptiveCard*, ABI::AdaptiveNamespace::AdaptiveActionEventArgs*>* handler,
        _Out_ EventRegistrationToken* token)
    {
        return m_actionEvents->Add(handler, token);
    }

    HRESULT RenderedAdaptiveCard::remove_Action(EventRegistrationToken token) { return m_actionEvents->Remove(token); }

    HRESULT RenderedAdaptiveCard::add_MediaClicked(
        _In_ ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveNamespace::RenderedAdaptiveCard*, ABI::AdaptiveNamespace::AdaptiveMediaEventArgs*>* handler,
        _Out_ EventRegistrationToken* token)
    {
        return m_mediaClickedEvents->Add(handler, token);
    }

    HRESULT RenderedAdaptiveCard::remove_MediaClicked(EventRegistrationToken token)
    {
        return m_mediaClickedEvents->Remove(token);
    }

    HRESULT RenderedAdaptiveCard::get_Errors(
        _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveError*>** value)
    {
        return m_errors.CopyTo(value);
    }

    HRESULT RenderedAdaptiveCard::get_Warnings(
        _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>** value)
    {
        return m_warnings.CopyTo(value);
    }

    HRESULT RenderedAdaptiveCard::SendActionEvent(_In_ IAdaptiveActionElement* actionElement)
    {
        // get the inputElements in Json form.
        ComPtr<IAdaptiveInputs> gatheredInputs;
        RETURN_IF_FAILED(get_UserInputs(&gatheredInputs));
        ComPtr<IAdaptiveActionEventArgs> eventArgs;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveActionEventArgs>(&eventArgs, actionElement, gatheredInputs.Get()));

        return m_actionEvents->InvokeAll(this, eventArgs.Get());
    }

    HRESULT RenderedAdaptiveCard::SendMediaClickedEvent(_In_ IAdaptiveMedia* mediaElement)
    {
        ComPtr<IAdaptiveMediaEventArgs> eventArgs;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveMediaEventArgs>(&eventArgs, mediaElement));

        return m_mediaClickedEvents->InvokeAll(this, eventArgs.Get());
    }

    void RenderedAdaptiveCard::SetFrameworkElement(_In_ ABI::Windows::UI::Xaml::IFrameworkElement* value)
    {
        m_frameworkElement = value;
    }

    void RenderedAdaptiveCard::SetOriginatingCard(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* value)
    {
        m_originatingCard = value;
    }

    HRESULT RenderedAdaptiveCard::AddInputValue(_In_ IAdaptiveInputValue* inputItem)
    {
        return m_inputs->AddInputValue(inputItem);
    }
}
