#include "pch.h"
#include "AdaptiveDateInput.h"
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
    HRESULT AdaptiveDateInput::RuntimeClassInitialize() noexcept try
    {
        m_sharedDateInput = std::make_shared<DateInput>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::DateInput>& sharedDateInput)
    {
        if (sharedDateInput == nullptr)
        {
            return E_INVALIDARG;
        }

        m_sharedDateInput = sharedDateInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Max(HSTRING* max)
    {
        return UTF8ToHString(m_sharedDateInput->GetMax(), max);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Max(HSTRING max)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(max, out));
        m_sharedDateInput->SetMax(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Min(HSTRING* min)
    {
        return UTF8ToHString(m_sharedDateInput->GetMin(), min);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Min(HSTRING min)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(min, out));
        m_sharedDateInput->SetMin(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Placeholder(HSTRING* placeholder)
    {
        return UTF8ToHString(m_sharedDateInput->GetPlaceholder(), placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Placeholder(HSTRING placeholder)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(placeholder, out));
        m_sharedDateInput->SetPlaceholder(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Value(HSTRING* value)
    {
        return UTF8ToHString(m_sharedDateInput->GetValue(), value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Value(HSTRING value)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(value, out));
        m_sharedDateInput->SetValue(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedDateInput->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedDateInput->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::DateInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Spacing(ABI::AdaptiveCards::Uwp::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::Uwp::Spacing>(m_sharedDateInput->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Spacing(ABI::AdaptiveCards::Uwp::Spacing spacing)
    {
        m_sharedDateInput->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_Separator(boolean* separator)
    {
        *separator = m_sharedDateInput->GetSeparator();
        return S_OK;

        //Issue #629 to make separator an object
        //return GenerateSeparatorProjection(m_sharedDateInput->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_Separator(boolean separator)
    {
        m_sharedDateInput->SetSeparator(separator);

        /*Issue #629 to make separator an object
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedDateInput->SetSeparator(sharedSeparator);
        */

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_sharedDateInput->GetIsRequired();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::put_IsRequired(boolean isRequired)
    {
        m_sharedDateInput->SetIsRequired(isRequired);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInput::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }

}}
