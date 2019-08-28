// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionSet.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    AdaptiveActionSet::AdaptiveActionSet() { m_actions = Microsoft::WRL::Make<Vector<IAdaptiveActionElement*>>(); }

    HRESULT AdaptiveActionSet::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveCards::ActionSet> ActionSet = std::make_shared<AdaptiveCards::ActionSet>();
        return RuntimeClassInitialize(ActionSet);
    }
    CATCH_RETURN;

    _Use_decl_annotations_ HRESULT AdaptiveActionSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ActionSet>& sharedActionSet)
    try
    {
        if (sharedActionSet == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(GenerateActionsProjection(sharedActionSet->GetActions(), m_actions.Get()));
        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedActionSet));
        return S_OK;
    }
    CATCH_RETURN;

    _Use_decl_annotations_ HRESULT AdaptiveActionSet::get_Actions(IVector<IAdaptiveActionElement*>** items)
    {
        return m_actions.CopyTo(items);
    }

    _Use_decl_annotations_ HRESULT AdaptiveActionSet::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::ActionSet;
        return S_OK;
    }

    HRESULT AdaptiveActionSet::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::ActionSet> actionSet = std::make_shared<AdaptiveCards::ActionSet>();
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveCards::BaseCardElement>(actionSet)));

        GenerateSharedActions(m_actions.Get(), actionSet->GetActions());

        sharedModel = actionSet;
        return S_OK;
    }
    CATCH_RETURN;
}
