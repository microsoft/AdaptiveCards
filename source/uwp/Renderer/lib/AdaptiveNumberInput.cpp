#include "pch.h"
#include "AdaptiveNumberInput.h"

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
    HRESULT AdaptiveNumberInput::RuntimeClassInitialize() noexcept try
    {
        m_sharedNumberInput = std::make_shared<NumberInput>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::NumberInput>& sharedNumberInput)
    {
        if (sharedNumberInput == nullptr)
        {
            return E_INVALIDARG;
        }

        m_sharedNumberInput = sharedNumberInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Placeholder(HSTRING* placeholder)
    {
        return UTF8ToHString(m_sharedNumberInput->GetPlaceholder(), placeholder);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Placeholder(HSTRING placeholder)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(placeholder, out));
        m_sharedNumberInput->SetPlaceholder(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Value(INT32* value)
    {
        *value = m_sharedNumberInput->GetValue();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Value(INT32 value)
    {
        m_sharedNumberInput->SetValue(value);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Max(INT32* max)
    {
        *max = m_sharedNumberInput->GetMax();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Max(INT32 max)
    {
        m_sharedNumberInput->SetMax(max);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Min(INT32* min)
    {
        *min = m_sharedNumberInput->GetMin();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Min(INT32 min)
    {
        m_sharedNumberInput->SetMin(min);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedNumberInput->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedNumberInput->SetId(out);
        return S_OK;
    }
    
    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::NumberInput;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Spacing(ABI::AdaptiveCards::Uwp::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::Uwp::Spacing>(m_sharedNumberInput->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Spacing(ABI::AdaptiveCards::Uwp::Spacing spacing)
    {
        m_sharedNumberInput->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_Separator(boolean* separator)
    {
        *separator = m_sharedNumberInput->GetSeparator();
        return S_OK;

        //Issue #629 to make separator an object
        //return GenerateSeparatorProjection(m_sharedNumberInput->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_Separator(boolean separator)
    {
        m_sharedNumberInput->SetSeparator(separator);

        /*Issue #629 to make separator an object
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedNumberInput->SetSeparator(sharedSeparator);
        */
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_IsRequired(boolean* isRequired)
    {
        *isRequired = m_sharedNumberInput->GetIsRequired();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::put_IsRequired(boolean isRequired)
    {
        m_sharedNumberInput->SetIsRequired(isRequired);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInput::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }

}}
