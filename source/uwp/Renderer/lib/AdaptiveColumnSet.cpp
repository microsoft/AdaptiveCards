#include "pch.h"
#include "AdaptiveColumnSet.h"

#include "Util.h"
#include "Vector.h"
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
    AdaptiveColumnSet::AdaptiveColumnSet()
    {
        m_columns = Microsoft::WRL::Make<Vector<IAdaptiveColumn*>>();
    }

    HRESULT AdaptiveColumnSet::RuntimeClassInitialize() noexcept try
    {
        m_sharedColumnSet = std::make_shared<ColumnSet>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ColumnSet>& sharedColumnSet)
    {
        if (sharedColumnSet == nullptr)
        {
            return E_INVALIDARG;
        }

        m_sharedColumnSet = sharedColumnSet;
        GenerateColumnsProjection(m_sharedColumnSet->GetColumns(), m_columns.Get());
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumnSet::get_Columns(IVector<IAdaptiveColumn*>** columns)
    {
        return m_columns.CopyTo(columns);
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumnSet::get_SelectAction(IAdaptiveActionElement** action)
    {
        return GenerateActionProjection(m_sharedColumnSet->GetSelectAction(), action);
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumnSet::put_SelectAction(IAdaptiveActionElement* action)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumnSet::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::ColumnSet;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSet::get_Spacing(ABI::AdaptiveCards::Uwp::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::Uwp::Spacing>(m_sharedColumnSet->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSet::put_Spacing(ABI::AdaptiveCards::Uwp::Spacing spacing)
    {
        m_sharedColumnSet->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSet::get_Separator(boolean* separator)
    {
        *separator = m_sharedColumnSet->GetSeparator();
        return S_OK;

        // Issue #629 to make separator an object
        //return GenerateSeparatorProjection(m_sharedColumnSet->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSet::put_Separator(boolean separator)
    {
        m_sharedColumnSet->SetSeparator(separator);

        /*Issue #629 to make separator an object
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedColumnSet->SetSeparator(sharedSeparator);
        */

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSet::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedColumnSet->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSet::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedColumnSet->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSet::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }
}}
