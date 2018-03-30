#include "pch.h"
#include "AdaptiveColumnSet.h"

#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>
#include "XamlHelpers.h"
#include "AdaptiveColumn.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespaceRef;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

AdaptiveNamespaceStart
    AdaptiveColumnSet::AdaptiveColumnSet()
    {
        m_columns = Microsoft::WRL::Make<Vector<IAdaptiveColumn*>>();
    }

    HRESULT AdaptiveColumnSet::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveCards::ColumnSet> columnSet = std::make_shared<AdaptiveCards::ColumnSet>();
        return RuntimeClassInitialize(columnSet);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ColumnSet>& sharedColumnSet) try
    {
        if (sharedColumnSet == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateColumnsProjection(sharedColumnSet->GetColumns(), m_columns.Get());
        GenerateActionProjection(sharedColumnSet->GetSelectAction(), &m_selectAction);

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedColumnSet));

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumnSet::get_Columns(IVector<IAdaptiveColumn*>** columns)
    {
        return m_columns.CopyTo(columns);
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumnSet::get_SelectAction(IAdaptiveActionElement** action)
    {
        return m_selectAction.CopyTo(action);
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumnSet::put_SelectAction(IAdaptiveActionElement* action)
    {
        m_selectAction = action;
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumnSet::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::ColumnSet;
        return S_OK;
    }

    HRESULT AdaptiveColumnSet::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveCards::ColumnSet> columnSet = std::make_shared<AdaptiveCards::ColumnSet>();
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveCards::BaseCardElement>(columnSet)));

        if (m_selectAction != nullptr)
        {
            std::shared_ptr<BaseActionElement> sharedAction;
            RETURN_IF_FAILED(GenerateSharedAction(m_selectAction.Get(), sharedAction));
            columnSet->SetSelectAction(sharedAction);
        }

        XamlHelpers::IterateOverVector<IAdaptiveColumn>(m_columns.Get(), [&](IAdaptiveColumn* column)
        {
            ComPtr<AdaptiveNamespaceRef::AdaptiveColumn> columnImpl = PeekInnards<AdaptiveNamespaceRef::AdaptiveColumn>(column);

            std::shared_ptr<BaseCardElement> sharedColumnBaseElement;
            RETURN_IF_FAILED(columnImpl->GetSharedModel(sharedColumnBaseElement));

            std::shared_ptr<AdaptiveCards::Column> sharedColumn = std::AdaptivePointerCast<AdaptiveCards::Column>(sharedColumnBaseElement);
            if (sharedColumn == nullptr)
            {
                return E_UNEXPECTED;
            }

            columnSet->GetColumns().push_back(sharedColumn);

            return S_OK;
        });

        sharedModel = columnSet;
        return S_OK;
    }CATCH_RETURN;
AdaptiveNamespaceEnd
