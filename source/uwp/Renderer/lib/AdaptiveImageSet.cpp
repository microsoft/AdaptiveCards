#include "pch.h"
#include "AdaptiveImageSet.h"

#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

AdaptiveNamespaceStart
    AdaptiveImageSet::AdaptiveImageSet()
    {
        m_images = Microsoft::WRL::Make<Vector<IAdaptiveImage*>>();
    }

    HRESULT AdaptiveImageSet::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ImageSet> imageSet = std::make_shared<AdaptiveSharedNamespace::ImageSet>();
        return RuntimeClassInitialize(imageSet);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::ImageSet>& sharedImageSet)
    {
        if (sharedImageSet == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateImagesProjection(sharedImageSet->GetImages(), m_images.Get());

        m_imageSize = static_cast<ABI::AdaptiveNamespace::ImageSize>(sharedImageSet->GetImageSize());

        m_spacing = static_cast<ABI::AdaptiveNamespace::Spacing>(sharedImageSet->GetSpacing());
        m_separator = sharedImageSet->GetSeparator();
        RETURN_IF_FAILED(UTF8ToHString(sharedImageSet->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedImageSet->GetAdditionalProperties(), &m_additionalProperties));

        return S_OK;
    }

    _Use_decl_annotations_
        IFACEMETHODIMP AdaptiveImageSet::get_Images(IVector<IAdaptiveImage*>** images)
    {
        return m_images.CopyTo(images);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::get_ImageSize(ABI::AdaptiveNamespace::ImageSize* imageSize)
    {
        *imageSize = m_imageSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::put_ImageSize(ABI::AdaptiveNamespace::ImageSize imageSize)
    {
        m_imageSize = imageSize;
        return S_OK; 
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveImageSet::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::ImageSet;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::get_Spacing(ABI::AdaptiveNamespace::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::put_Spacing(ABI::AdaptiveNamespace::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::get_Separator(boolean* separator)
    {
        *separator = m_separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::put_Separator(boolean separator)
    {
        m_separator = separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::get_Id(HSTRING* id)
    {
        return m_id.CopyTo(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::put_Id(HSTRING id)
    {
        return m_id.Set(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveSharedNamespace::ImageSet> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::ImageSet>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ImageSet> imageSet = std::make_shared<AdaptiveSharedNamespace::ImageSet>();

        RETURN_IF_FAILED(SetSharedElementProperties(this, std::AdaptivePointerCast<AdaptiveSharedNamespace::BaseCardElement>(imageSet)));

        imageSet->SetImageSize(static_cast<AdaptiveSharedNamespace::ImageSize>(m_imageSize));

        RETURN_IF_FAILED(GenerateSharedImages(m_images.Get(), imageSet->GetImages()));

        sharedModel = imageSet;
        return S_OK;
    }CATCH_RETURN;
AdaptiveNamespaceEnd
