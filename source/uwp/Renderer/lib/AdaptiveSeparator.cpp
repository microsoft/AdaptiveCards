#include "pch.h"
#include "AdaptiveSeparator.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "AdaptiveCardRendererComponent.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{

    HRESULT AdaptiveSeparator::RuntimeClassInitialize() noexcept try
    {
        m_sharedSeparator = std::make_shared<Separator>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveSeparator::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Separator>& sharedSeparator)
    {
        m_sharedSeparator = sharedSeparator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparator::get_Color(ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor* color)
    {
        *color = static_cast<ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor>(m_sharedSeparator->GetColor());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparator::put_Color(ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor color)
    {
        m_sharedSeparator->SetColor(static_cast<AdaptiveCards::ForegroundColor>(color));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparator::get_Thickness(ABI::AdaptiveCards::Rendering::Uwp::SeparatorThickness* thickness)
    {
        *thickness = static_cast<ABI::AdaptiveCards::Rendering::Uwp::SeparatorThickness>(m_sharedSeparator->GetThickness());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparator::put_Thickness(ABI::AdaptiveCards::Rendering::Uwp::SeparatorThickness thickness)
    {
        m_sharedSeparator->SetThickness(static_cast<AdaptiveCards::SeparatorThickness>(thickness));
        return S_OK;
    }
}}}
