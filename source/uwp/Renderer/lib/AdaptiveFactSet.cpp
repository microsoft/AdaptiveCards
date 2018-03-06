#include "pch.h"
#include "AdaptiveFactSet.h"

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
    AdaptiveFactSet::AdaptiveFactSet()
    {
        m_facts = Microsoft::WRL::Make<Vector<IAdaptiveFact*>>();
    }

    HRESULT AdaptiveFactSet::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveCards::FactSet> factSet = std::make_shared<AdaptiveCards::FactSet>();
        return RuntimeClassInitialize(factSet);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::FactSet>& sharedFactSet)
    {
        if (sharedFactSet == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateFactsProjection(sharedFactSet->GetFacts(), m_facts.Get());
        
        m_spacing = static_cast<ABI::AdaptiveCards::Rendering::Uwp::Spacing>(sharedFactSet->GetSpacing());
        m_separator = sharedFactSet->GetSeparator();
        RETURN_IF_FAILED(UTF8ToHString(sharedFactSet->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedFactSet->GetAdditionalProperties(), &m_additionalProperties));

        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveFactSet::get_Facts(IVector<IAdaptiveFact*>** facts)
    {
        return m_facts.CopyTo(facts);
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveFactSet::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::FactSet;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::get_Spacing(ABI::AdaptiveCards::Rendering::Uwp::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::put_Spacing(ABI::AdaptiveCards::Rendering::Uwp::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::get_Separator(boolean* separator)
    {
        *separator = m_separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::put_Separator(boolean separator)
    {
        m_separator = separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::get_Id(HSTRING* id)
    {
        return m_id.CopyTo(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::put_Id(HSTRING id)
    {
        return m_id.Set(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveCards::FactSet> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFactSet::GetSharedModel(std::shared_ptr<AdaptiveCards::FactSet>& sharedModel) try
    {
        std::shared_ptr<AdaptiveCards::FactSet> factSet = std::make_shared<AdaptiveCards::FactSet>();

        RETURN_IF_FAILED(SetSharedElementProperties(this, std::dynamic_pointer_cast<AdaptiveCards::BaseCardElement>(factSet)));
        RETURN_IF_FAILED(GenerateSharedFacts(m_facts.Get(), factSet->GetFacts()));

        sharedModel = factSet;

        return S_OK;
    }CATCH_RETURN;
}}}
