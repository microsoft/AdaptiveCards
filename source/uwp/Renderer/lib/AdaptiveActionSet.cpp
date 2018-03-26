#include "pch.h"
#include "AdaptiveActionSet.h"

#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    AdaptiveActionSet::AdaptiveActionSet()
    {
        m_actions = Microsoft::WRL::Make<Vector<IAdaptiveActionElement*>>();
    }

    HRESULT AdaptiveActionSet::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveCards::ActionSet> ActionSet = std::make_shared<AdaptiveCards::ActionSet>();
        return RuntimeClassInitialize(ActionSet);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveActionSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ActionSet>& sharedActionSet) try
    {
        if (sharedActionSet == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(GenerateActionsProjection(sharedActionSet->GetActions(), m_actions.Get()));
        m_orientation = static_cast<ABI::AdaptiveCards::Rendering::Uwp::ActionsOrientation>(sharedActionSet->GetOrientation());
        
        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedActionSet));
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveActionSet::get_Actions(IVector<IAdaptiveActionElement*>** items)
    {
        return m_actions.CopyTo(items);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionSet::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::ActionSet;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionSet::get_Orientation(ABI::AdaptiveCards::Rendering::Uwp::ActionsOrientation* orientation)
    {
        *orientation = m_orientation;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionSet::put_Orientation(ABI::AdaptiveCards::Rendering::Uwp::ActionsOrientation orientation)
    {
        m_orientation = orientation;
        return S_OK;
    }

    HRESULT AdaptiveActionSet::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveCards::ActionSet> actionSet = std::make_shared<AdaptiveCards::ActionSet>();
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveCards::BaseCardElement>(actionSet)));

        actionSet->SetOrientation(static_cast<AdaptiveCards::ActionsOrientation>(m_orientation));

        GenerateSharedActions(m_actions.Get(), actionSet->GetActions());

        sharedModel = actionSet;
        return S_OK;
    }CATCH_RETURN;
}}}
