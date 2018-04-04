#include "pch.h"
#include "RenderedAdaptiveCard.h"

#include "AdaptiveCard.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>
#include "XamlBuilder.h"
#include "XamlHelpers.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveActionEventArgs.h"
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

AdaptiveNamespaceStart
    RenderedAdaptiveCard::RenderedAdaptiveCard()
    {
    }

    HRESULT RenderedAdaptiveCard::RuntimeClassInitialize()
    {
        m_errors = Make<Vector<IAdaptiveError*>>();
        m_warnings = Make<Vector<IAdaptiveWarning*>>();
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveNamespace::AdaptiveInputs>(&m_inputs));
        m_events = std::make_shared<ActionEventSource>();
        return S_OK;
    }

    HRESULT RenderedAdaptiveCard::RuntimeClassInitialize(
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveError*>* errors,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveWarning*>* warnings)
    {
        m_errors = errors;
        m_warnings = warnings;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveNamespace::AdaptiveInputs>(&m_inputs));
        m_events = std::make_shared<ActionEventSource>();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT RenderedAdaptiveCard::get_OriginatingCard(IAdaptiveCard** value)
    {
        return m_originatingCard.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT RenderedAdaptiveCard::get_FrameworkElement(IFrameworkElement** value)
    {
        return m_frameworkElement.CopyTo(value);
    }
    
    _Use_decl_annotations_
    HRESULT RenderedAdaptiveCard::get_UserInputs(ABI::AdaptiveNamespace::IAdaptiveInputs** value)
    {
        return m_inputs.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT RenderedAdaptiveCard::add_Action(
        ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveNamespace::RenderedAdaptiveCard*, ABI::AdaptiveNamespace::AdaptiveActionEventArgs*>* handler,
        EventRegistrationToken* token)
    {
        return m_events->Add(handler, token);
    }

    _Use_decl_annotations_
    HRESULT RenderedAdaptiveCard::remove_Action(EventRegistrationToken token)
    {
        return m_events->Remove(token);
    }

    _Use_decl_annotations_
    HRESULT RenderedAdaptiveCard::get_Errors(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveError*>** value)
    {
        return m_errors.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT RenderedAdaptiveCard::get_Warnings(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveWarning*>** value)
    {
        return m_warnings.CopyTo(value);
    }

    HRESULT RenderedAdaptiveCard::SendActionEvent(IAdaptiveActionElement* actionElement)
    {
        // get the inputElements in Json form.
        ComPtr<IAdaptiveInputs> gatheredInputs;
        RETURN_IF_FAILED(get_UserInputs(&gatheredInputs));
        ComPtr<IAdaptiveActionEventArgs> eventArgs;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveActionEventArgs>(&eventArgs, actionElement, gatheredInputs.Get()));

        return m_events->InvokeAll(this, eventArgs.Get());
    }

    void RenderedAdaptiveCard::SetFrameworkElement(ABI::Windows::UI::Xaml::IFrameworkElement* value)
    {
        m_frameworkElement = value;
    }

    void RenderedAdaptiveCard::SetOriginatingCard(ABI::AdaptiveNamespace::IAdaptiveCard* value)
    {
        m_originatingCard = value;
    }

    HRESULT RenderedAdaptiveCard::AddInputValue(IAdaptiveInputValue* inputItem)
    {
        return m_inputs->AddInputValue(inputItem);
    }
AdaptiveNamespaceEnd
