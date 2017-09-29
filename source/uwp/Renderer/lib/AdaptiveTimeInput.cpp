#include "pch.h"
#include "AdaptiveTimeInput.h"

#include "Util.h"
#include <windows.foundation.collections.h>
#include "AdaptiveCardRendererComponent.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveTimeInput::RuntimeClassInitialize() noexcept try
    {
        m_sharedTimeInput = std::make_shared<TimeInput>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TimeInput>& sharedTimeInput)
    {
        if (sharedTimeInput == nullptr)
        {
            return E_INVALIDARG;
        }

        m_sharedTimeInput = sharedTimeInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Max(HSTRING* max)
    {
        return UTF8ToHString(m_sharedTimeInput->GetMax(), max);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Max(HSTRING max)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(max, out));
        m_sharedTimeInput->SetMax(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveTimeInput::get_Min(HSTRING* min)
    {
        return UTF8ToHString(m_sharedTimeInput->GetMin(), min);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveTimeInput::put_Min(HSTRING min)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(min, out));
        m_sharedTimeInput->SetMin(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveTimeInput::get_Placeholder(HSTRING* placeholder)
    {
        return UTF8ToHString(m_sharedTimeInput->GetPlaceholder(), placeholder);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveTimeInput::put_Placeholder(HSTRING placeholder)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(placeholder, out));
        m_sharedTimeInput->SetPlaceholder(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Value(HSTRING* value)
    {
        return UTF8ToHString(m_sharedTimeInput->GetValue(), value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Value(HSTRING value)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(value, out));
        m_sharedTimeInput->SetValue(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedTimeInput->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedTimeInput->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::TimeInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Spacing(ABI::AdaptiveCards::Uwp::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::Uwp::Spacing>(m_sharedTimeInput->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Spacing(ABI::AdaptiveCards::Uwp::Spacing spacing)
    {
        m_sharedTimeInput->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_Separator(boolean* separator)
    {
        *separator = m_sharedTimeInput->GetSeparator();
        return S_OK;

        //Issue #629 to make separator an object
        //return GenerateSeparatorProjection(m_sharedTimeInput->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_Separator(boolean separator)
    {
        m_sharedTimeInput->SetSeparator(separator);

        /*Issue #629 to make separator an object
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedTimeInput->SetSeparator(sharedSeparator);
        */
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_sharedTimeInput->GetIsRequired();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::put_IsRequired(boolean isRequired)
    {
        m_sharedTimeInput->SetIsRequired(isRequired);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInput::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }
}}
