#include "pch.h"
#include "AdaptiveImageSet.h"

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
    AdaptiveImageSet::AdaptiveImageSet()
    {
        m_images = Microsoft::WRL::Make<Vector<IAdaptiveImage*>>();
    }

    HRESULT AdaptiveImageSet::RuntimeClassInitialize() noexcept try
    {
        m_sharedImageSet = std::make_shared<ImageSet>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ImageSet>& sharedImageSet)
    {
        if (sharedImageSet == nullptr)
        {
            return E_INVALIDARG;
        }

        m_sharedImageSet = sharedImageSet;
        GenerateImagesProjection(m_sharedImageSet->GetImages(), m_images.Get());
        return S_OK;
    }

    _Use_decl_annotations_
        IFACEMETHODIMP AdaptiveImageSet::get_Images(IVector<IAdaptiveImage*>** images)
    {
        return m_images.CopyTo(images);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::get_ImageSize(ABI::AdaptiveCards::Uwp::ImageSize* imageSize)
    {
        *imageSize = static_cast<ABI::AdaptiveCards::Uwp::ImageSize>(m_sharedImageSet->GetImageSize());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::put_ImageSize(ABI::AdaptiveCards::Uwp::ImageSize imageSize)
    {
        m_sharedImageSet->SetImageSize(static_cast<AdaptiveCards::ImageSize>(imageSize));
        return S_OK; 
    }

    _Use_decl_annotations_
        IFACEMETHODIMP AdaptiveImageSet::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::ImageSet;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::get_Spacing(ABI::AdaptiveCards::Uwp::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::Uwp::Spacing>(m_sharedImageSet->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::put_Spacing(ABI::AdaptiveCards::Uwp::Spacing spacing)
    {
        m_sharedImageSet->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::get_Separator(boolean* separator)
    {
        *separator = m_sharedImageSet->GetSeparator();
        return S_OK;

        //Issue #629 to make separator an object
        //return GenerateSeparatorProjection(m_sharedImageSet->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::put_Separator(boolean separator)
    {
        m_sharedImageSet->SetSeparator(separator);

        /*Issue #629 to make separator an object
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedImageSet->SetSeparator(sharedSeparator);
        */

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedImageSet->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedImageSet->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSet::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }
}
}